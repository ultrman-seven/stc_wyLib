#include "string.h"
#include "stcSys.h"

sysTime_t __sysTime = {
    0, 0, 0, 0
#if __STC_LIB_Sys_Time_UseHour
    ,
    0
#if __STC_LIB_Sys_Time_UseDay
    ,
    0
#endif
#endif
};

volatile unsigned int __sysMsDelayCnt = 0;

void sysInit()
{
    STC_IRQ_Enable();
    // 1000us@12.000MHz
#ifndef __STC_LIB_Sys_Timer_Index
#error "Please define __STC_LIB_Sys_Timer_Index in stcLibCfgExample.h"
#elif (__STC_LIB_Sys_Timer_Index == 0)
    AUXR |= 0x80;
    TMOD &= 0xF0;
    TL0 = 0x20;
    TH0 = 0xD1;
    TF0 = 0;
    TR0 = 1;

    ET0 = 1;
#elif (__STC_LIB_Sys_Timer_Index == 1)
#endif
}

void __sysTimerIrqHandler(void)
#if (__STC_LIB_Sys_Timer_Index == 0)
    STC_Interrupt(STC_InterruptNumTimer0)
#endif
{
    if (__sysMsDelayCnt)
        --__sysMsDelayCnt;
    if (++__sysTime.ms < 1000)
        return;
    __sysTime.ms = 0;
    if (++__sysTime.sec < 60)
        return;
    __sysTime.sec = 0;
    ++__sysTime.min;

#if __STC_LIB_Sys_Time_UseHour
    if (__sysTime.min < 60)
        return;
    __sysTime.min = 0;
    ++__sysTime.hour;
#if __STC_LIB_Sys_Time_UseDay

    if (__sysTime.hour < 24)
        return;
    __sysTime.hour = 0;
    ++__sysTime.day;
#endif
#endif
}

void sysDelayMs(unsigned int ms)
{
    volatile unsigned char i;
    unsigned int xdata msCnt;
    STC_IRQ_Disable();
    __sysMsDelayCnt = ms;
    STC_IRQ_Enable();
    while (1)
    {
        i = 38;

        STC_IRQ_Disable();
        msCnt = __sysMsDelayCnt;
        STC_IRQ_Enable();
        if (msCnt == 0)
            return;

        while (--i)
            ;
    }
}

// void sysDelayUs(unsigned int us)
// {
// }

void sysGetTimeStamp(sysTime_t *timePtr)
{
    unsigned int xdata timerCnt;
    if (NULL == timePtr)
        return;

#if __STC_LIB_Sys_Timer_Index == 0
    TR0 = 0; // stop timer
    timerCnt = (TH0 << 8) | TL0;
#endif

    timePtr->ms = __sysTime.ms;

    if (timePtr->ms < 999)
    {
#if __STC_LIB_Sys_Timer_Index == 0
        TR0 = 1; // start timer
#endif

        timePtr->sec = __sysTime.sec;
        timePtr->min = __sysTime.min;
#if __STC_LIB_Sys_Time_UseHour
        timePtr->hour = __sysTime.hour;
#if __STC_LIB_Sys_Time_UseDay
        timePtr->day = __sysTime.day;
#endif
#endif
    }
    else
    {
        timePtr->sec = __sysTime.sec;
        timePtr->min = __sysTime.min;
#if __STC_LIB_Sys_Time_UseHour
        timePtr->hour = __sysTime.hour;
#if __STC_LIB_Sys_Time_UseDay
        timePtr->day = __sysTime.day;
#endif
#endif

#if __STC_LIB_Sys_Timer_Index == 0
        TR0 = 1; // start timer
#endif
    }

    timerCnt = 0xFFFF - timerCnt;
    timerCnt /= 12; // 12MHz
    // __sysTime.us = timerCnt;
    timePtr->us = timerCnt;
}

#if __STC_LIB_Sys_Time_USE_MinusUs
unsigned int sysTimeMinusUs(sysTime_t *start, sysTime_t *end)
{
    unsigned int xdata us = 0;
    sysTime_t xdata t;
    if (NULL == start || NULL == end)
        return 0;

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    t.day = end->day - start->day;
    if (end->hour >= start->hour)
        t.hour = end->hour - start->hour;
    else
    {
        --t.day;
        t.hour = 24 - start->hour + end->hour;
    }
#else
    t.hour = end->hour - start->hour;
#endif
    if (end->min >= start->min)
        t.min = end->min - start->min;
    else
    {
        --t.hour;
        t.min = 60 - start->min + end->min;
    }
#else
    t.min = end->min - start->min;
#endif

    if (end->sec >= start->sec)
        t.sec = end->sec - start->sec;
    else
    {
        --t.min;
        t.sec = 60 - start->sec + end->sec;
    }
    if (end->ms >= start->ms)
        t.ms = end->ms - start->ms;
    else
    {
        --t.sec;
        t.ms = 1000 - start->ms + end->ms;
    }
    if (end->us >= start->us)
        t.us = end->us - start->us;
    else
    {
        --t.ms;
        t.us = 1000 - start->us + end->us;
    }

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    if (t.day)
        return 0xffff;
#endif
    if (t.hour)
        return 0xffff;
#endif
    if (t.min)
        return 0xffff;
    if (t.sec)
        return 0xffff;
    if (t.ms > 64)
        return 0xffff;
    us = t.us + t.ms * 1000;
    return us;
}
#endif

#if __STC_LIB_Sys_Time_USE_MinusMs
unsigned int sysTimeMinusMs(sysTime_t *start, sysTime_t *end)
{
    unsigned int xdata ms = 0;
    sysTime_t xdata t;
    if (NULL == start || NULL == end)
        return 0;

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    t.day = end->day - start->day;
    if (end->hour >= start->hour)
        t.hour = end->hour - start->hour;
    else
    {
        t.day -= 1;
        t.hour = 24 - start->hour + end->hour;
    }
#else
    t.hour = end->hour - start->hour;
#endif
    if (end->min >= start->min)
        t.min = end->min - start->min;
    else
    {
        --t.hour;
        t.min = 60 - start->min + end->min;
    }
#else
    t.min = end->min - start->min;
#endif

    if (end->sec >= start->sec)
        t.sec = end->sec - start->sec;
    else
    {
        --t.min;
        t.sec = 60 - start->sec + end->sec;
    }
    if (end->ms >= start->ms)
        t.ms = end->ms - start->ms;
    else
    {
        --t.sec;
        t.ms = 1000 - start->ms + end->ms;
    }
    if (end->us >= start->us)
        t.us = end->us - start->us;
    else
    {
        --t.ms;
        t.us = 1000 - start->us + end->us;
    }

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    if (t.day)
        return 0xffff;
#endif
    if (t.hour)
        return 0xffff;
#endif
    if (t.min)
        return 0xffff;

    ms = t.ms + t.sec * 1000;
    if (t.us > 600)
        ++ms;
    return ms;
}
#endif

#if __STC_LIB_Sys_Time_USE_MinusSec
unsigned int sysTimeMinusSec(sysTime_t *start, sysTime_t *end)
{
    unsigned int xdata sec = 0;
    sysTime_t xdata t;
    if (NULL == start || NULL == end)
        return 0;

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    t.day = end->day - start->day;
    if (end->hour >= start->hour)
        t.hour = end->hour - start->hour;
    else
    {
        t.day -= 1;
        t.hour = 24 - start->hour + end->hour;
    }
#else
    t.hour = end->hour - start->hour;
#endif
    if (end->min >= start->min)
        t.min = end->min - start->min;
    else
    {
        t.hour -= 1;
        t.min = 60 - start->min + end->min;
    }
#else
    t.min = end->min - start->min;
#endif

    if (end->sec >= start->sec)
        t.sec = end->sec - start->sec;
    else
    {
        t.min -= 1;
        t.sec = 60 - start->sec + end->sec;
    }
    if (end->ms >= start->ms)
        t.ms = end->ms - start->ms;
    else
    {
        t.sec -= 1;
        t.ms = 1000 - start->ms + end->ms;
    }

#if __STC_LIB_Sys_Time_UseHour
#if __STC_LIB_Sys_Time_UseDay
    if (t.day)
        return 0xffff;
#endif
    if (t.hour >= 18)
        return 0xffff;
#endif
    sec = t.sec + t.min * 60;
    if (t.ms > 600)
        ++sec;
    return sec;
}
#endif
