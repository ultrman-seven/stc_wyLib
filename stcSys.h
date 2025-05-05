#ifndef D95C7B95_B12D_4242_AE07_3C44E6A2C258
#define D95C7B95_B12D_4242_AE07_3C44E6A2C258

#include "stcChip.h"

typedef struct
{
    unsigned int us;
    unsigned int ms;
    unsigned char sec;
    unsigned char min;
#if __STC_LIB_Sys_Time_UseHour
    unsigned char hour;
#if __STC_LIB_Sys_Time_UseDay
    unsigned char day;
#endif
#endif
} sysTime_t;

void sysInit();
void sysDelayMs(unsigned int ms);
void sysGetTimeStamp(sysTime_t *timePtr);
unsigned int sysTimeMinusUs(sysTime_t *start, sysTime_t *end);
unsigned int sysTimeMinusMs(sysTime_t *start, sysTime_t *end);
unsigned int sysTimeMinusSec(sysTime_t *start, sysTime_t *end);
#endif /* D95C7B95_B12D_4242_AE07_3C44E6A2C258 */
