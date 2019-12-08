# STM8S UART1 Transceiver

## What is it?

It is an opinionated firmware for utilizing UART1 of STM8 devices.

## What's opinionated about this firmware?

The firmware shipped with sane defaults. There is no choice of implementation variants.
The firmware always operates UART in 9-bit mode eight data bit and one parity bit.
The only parity mode supported is the even parity.  
The only essential configuration is the clock.

## Which devices are supported by this firmware?

See the readme of [the underlying headers for the list of supported devices](https://github.com/the-cave/stm8s-header/blob/sdcc-patched/README.md#currently-supported-targets).

## Dependencies

* [STM8S header](https://github.com/the-cave/stm8s-header)

## How to use the library?

- First, adding this library and its dependencies to your project.  
You can accomplish this in numerous ways depends on your setup. The opinionated way to do it is by using the [git submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) and the [Universal STM8 Builder](https://github.com/midnight-wonderer/universal-stm8-builder).
- Include the firmware header to where you wanted to use the firmware
  ~~~c
  #include "stm8s_uart1_transceiver.h"
  ~~~
- Configure the clock for the UART module
  ~~~c
  stm8s_uart1__setup_clock(0x1a, 0x01);
  // The magic numbers here are BRR1 and BRR2 respectively
  // 0x1a, and 0x01 are for running UART at 4800 bps on master clock of 2MHz
  //
  // Please refer to section 22.3.4 on RM0016 paper released by ST for more information.
  ~~~
- Then depends on what you wanted to do you can:
  - Use the receiver
    - Declare the handler function
      ~~~c
      static void data_handler(uint8_t data) {
        // do something with "data"
      }
      ~~~
    - Setup the receiver
      ~~~c
      static const stm8sUart1_ReceiverConfig receiver_config = {
        .data_received = &data_handler,
        // notice: optionally you can declare what to do when data error too
        // .overrun_detected = &uart_error_handler,
        // .data_error_detected = &uart_error_handler,
      };
      ~~~
  - Send some data via the UART port
    - Check if the device is ready for buffering more data
      ~~~c
      if (stm8s_uart1__is_ready())
      ~~~
    - Send the data (to the device buffer)
      ~~~c
      stm8s_uart1__send(data);
      ~~~

## Disabling receiver or transmitter
The library can be compiled with `STM8S_UART1__DISABLE_RECEIVER` or `STM8S_UART1__DISABLE_TRANSMITTER` flags.

## License

STM8S UART1 Transceiver is released under the [BSD 3-Clause License](LICENSE.md). :tada:
