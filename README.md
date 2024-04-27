# stc_wyLib

![GitHub License](https://img.shields.io/github/license/ultrman-seven/mm32_wyLib) ![stc](https://img.shields.io/badge/STC-LIB-blue) ![update](https://img.shields.io/github/created-at/ultrman-seven/mm32_wyLib) ![size](https://img.shields.io/github/directory-file-count/ultrman-seven/mm32_wyLib)

This is a hardware abstraction layer library for [STC](https://www.stcaimcu.com/) MCU.

**NOTE**: You should define your chip model in keil first.

The chip model list is as follows:

|model|define|
|:-------|:--------:|
|STC8H|`_ChipSTC8H`|
|STC8G|`_ChipSTC8G`|

`PS`: *Almost half of the abstraction level, because C51 is too difficult to abstract.*

If it weren't for being so **cheap**, let the 51 go to hell and then go embrace my [STM32](https://github.com/ultrman-seven/stm32CppHAL) and [MM32](https://github.com/ultrman-seven/mm32_wyLib) HAL library.

## Use Guide

### GPIO

+ Initialization function: `void gpioInit(const char *pinName, GpioMode m)`

example:

```C
#define led1 P30
#define led2 P31
#define led3 P32

void main()
{
    gpioInit(gpioPin2Str(led1),GpioModePP);
    gpioInit(gpioPin2Str(led2),GpioModePP);
    gpioInit(gpioPin2Str(led3),GpioModePP);

    led1 = led2 =led3 = 1;
    while(1)
        ;
}
```

### UART

### SPI

### IIC

### ADC

### DMA
