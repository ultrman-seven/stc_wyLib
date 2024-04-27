#ifndef B3BB5DF2_1561_4F75_A67D_9CED9BAD084D
#define B3BB5DF2_1561_4F75_A67D_9CED9BAD084D

typedef enum
{
    GpioModeQuasiIO = 0x00,
    GpioModePP,
    GpioModeOD = 0x03,
    GpioModeInAnalog = 0x02,
    GpioModeInFloating = 0x12,
    // GpioModeIPD = 0x22,
    GpioModeIPU = 0x32

} GpioMode;
#define __Gpio_Pin2String(_Gpio_Pin) #_Gpio_Pin
#define gpioPin2Str(_Gpio_Pin) __Gpio_Pin2String(_Gpio_Pin)
void gpioInit(const char *pinName, GpioMode m);
#endif /* B3BB5DF2_1561_4F75_A67D_9CED9BAD084D */
