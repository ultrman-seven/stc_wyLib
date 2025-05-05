#ifndef __STC_LIB_GPIO_H__
#define __STC_LIB_GPIO_H__

#include "stcSys.h"

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

#if __STC_LIB_GPIO_USE_KeyFSM
typedef struct
{
    sysTime_t _t;
    struct{
        unsigned char fsmState : 4;
        unsigned char pressCnt : 4;
        // unsigned char longPress : 1;
        // unsigned char doublePress : 1;
    } _state;
    void (*shortPressCallback)(unsigned char pressCnt);
    void (*longPressCallback)();
    // void (*doublePressCallback)();
    unsigned char (*readKey)();
} GpioKeyFsmCore;
#endif

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

#if __STC_LIB_GPIO_USE_KeyFSM
void gpioKeyFsmInit(GpioKeyFsmCore *core, unsigned char (*readKey)());
void gpioKeyFsmRun(GpioKeyFsmCore *core);
#endif

#endif /* __STC_LIB_GPIO_H__ */
