// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#include "stm8s_uart1_transceiver.h"

static void (*data_received)(uint8_t data);
static void (*overrun_detected)(void);
static void (*data_error_detected)(void);

void stm8s_uart1_transceiver__setup_receiver(
    stm8sUart1Transceiver_ReceiverConfig* config) {
  if (!config->data_received)
    return;
  UART1->CR1 |= UART1_CR1_PIEN | UART1_CR1_PCEN | UART1_CR1_M;
  CLK->PCKENR1 |= CLK_PCKENR1_UART1;
  overrun_detected = config->overrun_detected;
  data_error_detected = config->data_error_detected;
  data_received = config->data_received;
  UART1->CR2 |= UART1_CR2_RIEN | UART1_CR2_REN;
}

INTERRUPT_HANDLER(stm8s_uart1_transceiver__receive_handler, ITC_IRQ_UART1_RX) {
  uint8_t status = UART1->SR;
  // no need to check here as we already checked before enable the interrupt
  // if (!data_received)
  if (status & UART1_SR_OR) {  // overrun
    data_received(UART1->DR);
    if (overrun_detected)
      overrun_detected();
    return;
  }
  if (status & (UART1_SR_PE |  // parity error
                UART1_SR_NF |  // noise detected
                UART1_SR_FE |  // framing error (mismatched stop bit)
                0)) {
    status = UART1->DR;  // discard the data
    if (data_error_detected)
      data_error_detected();
    return;
  }
  if (status & UART1_SR_RXNE) {  // ready to read
    data_received(UART1->DR);
  }
}
