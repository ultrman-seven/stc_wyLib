#include "stcChip.h"
#include "stcGpio.h"

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
    unsigned char pin, mask;
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
