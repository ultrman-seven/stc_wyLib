#include "stcChip.h"
#include "stcGpio.h"

// 软件去抖动时间
#define __GPIO_KEY_FSM_ANTI_SHAKE_TIME_MS 50
// 长按时间
#define __GPIO_KEY_FSM_LONG_PRESS_TIME_MS 1500
// 连击间隔时间
#define __GPIO_KEY_FSM_DOUBLE_PRESS_TIME_MS 200

#define __GPIO_INIT_SWITCH_CASE(__PORT) \
    case __PORT:                        \
        if (m & 0x01)                   \
            P##__PORT##M0 |= mask;      \
        else                            \
            P##__PORT##M0 &= ~mask;     \
        if (m & 0x02)                   \
            P##__PORT##M1 |= mask;      \
        else                            \
            P##__PORT##M1 &= ~mask;     \
        if (m & 0x10)                   \
            P##__PORT##IE |= mask;      \
        if (m & 0x20)                   \
        {                               \
            P##__PORT##PU |= mask;      \
            P##__PORT## |= mask;        \
        }                               \
        break

void gpioInit(const char *pinName, GpioMode m)
{
    unsigned char xdata pin, mask;
    P_SW2 |= 0x80;

    mask = 0x01;

    if (*pinName == 'P' || *pinName == 'p')
        ++pinName;
    pin = pinName[1] - '0';

    mask <<= pin;

    switch (*pinName - '0')
    {
        __GPIO_INIT_SWITCH_CASE(0);
        __GPIO_INIT_SWITCH_CASE(1);
        __GPIO_INIT_SWITCH_CASE(2);
        __GPIO_INIT_SWITCH_CASE(3);
        __GPIO_INIT_SWITCH_CASE(4);
        __GPIO_INIT_SWITCH_CASE(5);
        __GPIO_INIT_SWITCH_CASE(6);
        __GPIO_INIT_SWITCH_CASE(7);
    default:
        break;
    }
    P_SW2 &= 0x7f;
}

#if __STC_LIB_GPIO_USE_KeyFSM
typedef enum
{
    GpioKeyFsmStateIdle = 0,
    GpioKeyFsmStateAntiPressShake,
    GpioKeyFsmStateAntiReleaseShake,
    GpioKeyFsmStateWaitLongPressRelease,
    // GpioKeyFsmStateWaitDoublePress,
    GpioKeyFsmStateWaitRelease,
    GpioKeyFsmStateWaitNextClick,
} GpioKeyFsmState;

void gpioKeyFsmInit(GpioKeyFsmCore *core, unsigned char (*readKey)())
{
    core->_state.fsmState = GpioKeyFsmStateIdle;
    core->_state.pressCnt = 0;
    core->readKey = readKey;
    // sysGetTimeStamp(&core->_t);
}

void gpioKeyFsmRun(GpioKeyFsmCore *core)
{
    switch (core->_state.fsmState)
    {
    case GpioKeyFsmStateIdle:
        if (core->readKey())
        {
            sysGetTimeStamp(&core->_t);
            core->_state.fsmState = GpioKeyFsmStateAntiPressShake;
        }
        break;
    case GpioKeyFsmStateAntiPressShake:
    {
        sysTime_t xdata t;
        sysGetTimeStamp(&t);
        if (sysTimeMinusMs(&core->_t, &t) > __GPIO_KEY_FSM_ANTI_SHAKE_TIME_MS)
        {
            if (core->readKey())
            {
                // if (core->longPressCallback)
                //     core->_state.fsmState = GpioKeyFsmStateWaitLongPress;
                // else
                core->_state.fsmState = GpioKeyFsmStateWaitRelease;

                if (core->shortPressCallback)
                    core->shortPressCallback(++core->_state.pressCnt);
            }
            core->_state.fsmState = GpioKeyFsmStateIdle;
            core->_state.pressCnt = 0;
        }
    }
    break;

    // case GpioKeyFsmStateWaitLongPress:
    // {
    //     sysTime_t xdata t;
    //     sysGetTimeStamp(&t);
    //     if (sysTimeMinusMs(&core->_t, &t) > 1000)
    //     {
    //         if (core->longPressCallback)
    //             core->longPressCallback();
    //         core->_state.fsmState = GpioKeyFsmStateWaitRelease;
    //     }
    // }
    // break;
    case GpioKeyFsmStateWaitRelease:
        if (!core->readKey())
        {
            sysGetTimeStamp(&core->_t);
            core->_state.fsmState = GpioKeyFsmStateWaitNextClick;
        }
        else
        {
            sysTime_t xdata t;
            sysGetTimeStamp(&t);
            if (sysTimeMinusMs(&core->_t, &t) > __GPIO_KEY_FSM_LONG_PRESS_TIME_MS)
            {
                if (core->longPressCallback)
                    core->longPressCallback();
                core->_state.fsmState = GpioKeyFsmStateWaitLongPressRelease;
            }
        }
        break;

    case GpioKeyFsmStateWaitLongPressRelease:
        if (!core->readKey())
        {
            sysGetTimeStamp(&core->_t);
            core->_state.fsmState = GpioKeyFsmStateIdle;
        }
        break;
    default:
        break;
    }
}
#endif
