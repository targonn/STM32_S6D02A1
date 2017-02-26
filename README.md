# STM32_S6D02A1
STM32 Library for S6D02A1 1.8 TFT 128x160 SPI screen

Code in early development and hopefully will be regularly updated. Compiled from multiple sources, mostly based on Arduino libraries.

Hardware SPI, HAL library.

Tested with STM32F103C8T6 maple clone connected to SPI1 transmit only master at 18MHz( SPI prescaler 4 at 72MHz clock)

Frame format Motorola
Data Size 8 bits
First Bit MSB
Prescaler 4
CPOL Low
CPHA 1 Edge
CRC Disabled

Configured with STM32CUBEMX, imported to Keil uVision v5

