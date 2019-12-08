// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#ifndef __STM8S_UART1_TRANSCEIVER_H
#define __STM8S_UART1_TRANSCEIVER_H

#include <stdint.h>
#include "stm8s.h"
#include "stm8s_itc.h"
#include "stm8s_uart1.h"

// refer to RM0016 for BRR settings
// see section 22.3.4
// the bit arrangement is kinda tricky
//
// example:
// assuming f=2Mhz
//
// generating 14400 baud rate would requires
// BRR1=0x08, BRR2=0x0b
//
// generating 4800 baud rate would requires
// BRR1=0x1a, BRR2=0x01

#define stm8s_uart1__setup_clock(brr1, brr2) \
  do {                                       \
    UART1->BRR2 = (brr2);                    \
    UART1->BRR1 = (brr1);                    \
  } while (0)

#ifndef STM8S_UART1__DISABLE_RECEIVER
INTERRUPT_HANDLER(stm8s_uart1__receive_handler, ITC_IRQ_UART1_RX);

typedef struct _stm8s_uart1__receiver_config {
  void (*data_received)(uint8_t data);
  void (*overrun_detected)(void);
  void (*data_error_detected)(void);
} stm8sUart1_ReceiverConfig;

void stm8s_uart1__setup_receiver(stm8sUart1_ReceiverConfig* config);
#endif

#ifndef STM8S_UART1__DISABLE_TRANSMITTER

void stm8s_uart1__setup_transmitter(void);

#define stm8s_uart1__is_ready() (UART1->SR & UART1_SR_TXE)

#define stm8s_uart1__send(data) \
  do {                          \
    UART1->DR = (data);         \
  } while (0)
#endif

#endif
