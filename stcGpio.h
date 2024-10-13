#ifndef __STC_LIB_GPIO_H__
#define __STC_LIB_GPIO_H__

typedef enum
{
    GpioModeQuasiIO = 0x00,
    GpioModePP,
    GpioModeOD = 0x03,
    GpioModeOD_PU = 0x23,
    GpioModeInAnalog = 0x02,
    GpioModeInFloating = 0x12,
    // GpioModeIPD = 0x22,
    GpioModeIPU = 0x32

} GpioMode;

#define gpioEnableInput(_Port, _Pin) \
    do                               \
    {                                \
        unsigned char mask = 0x01;   \
        P_SW2 |= 0x80;               \
        mask <<= _Pin;               \
        P##_Port##IE |= mask;        \
        P_SW2 &= 0x7f;               \
    } while (0);
#define gpioDisableInput(_Port, _Pin) \
    do                                \
    {                                 \
        unsigned char mask = 0x01;    \
        P_SW2 |= 0x80;                \
        mask <<= _Pin;                \
        mask = ~mask;                 \
        P##_Port##IE &= mask;         \
        P_SW2 &= 0x7f;                \
    } while (0);

#define __Gpio_Pin2String(_Gpio_Pin) #_Gpio_Pin
#define gpioPin2Str(_Gpio_Pin) __Gpio_Pin2String(_Gpio_Pin)
void gpioInit(const char *pinName, GpioMode m);
#endif /* __STC_LIB_GPIO_H__ */
