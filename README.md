# STM8S UART1 Transceiver

## What is it?

It is an opinionated firmware for utilizing UART1 of STM8 devices.

## What's opinionated about this firmware?

The firmware shipped with sane defaults. There is no choice of implementation variants.
The firmware always operates UART in 9-bit mode eight data bit and one parity bit.
The only parity mode supported is the even parity.  
The only essential configuration is the clock.

## Dependencies

* [STM8S header](https://github.com/the-cave/stm8s-header)

## Which devices are supported by this firmware?

See the readme of [the underlying headers for list of supported devices](https://github.com/the-cave/stm8s-header/blob/sdcc-patched/README.md#currently-supported-targets).

## License

STM8S UART1 Transceiver is released under the [BSD 3-Clause License](LICENSE.md). :tada:
