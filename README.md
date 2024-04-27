# stc_wyLib

This is a hardware abstraction layer library for STC MCU.

PS: Almost half of the abstraction level, because C51 is too difficult to abstract.

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
