// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#include "stm8s_uart1_transceiver.h"

void stm8s_uart1__setup_transmitter(void) {
  UART1->CR1 |= UART1_CR1_PCEN | UART1_CR1_M;
  CLK->PCKENR1 |= CLK_PCKENR1_UART1;
  UART1->CR2 |= UART1_CR2_TEN;
}
