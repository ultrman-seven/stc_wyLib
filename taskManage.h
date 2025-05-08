#ifndef __STC_LIB_TASK_H__
#define __STC_LIB_TASK_H__

#include "stcSys.h"

#if __STC_LIB_Task_USE_TaskCountTrigger
typedef struct
{
    void (*task)(void);
    unsigned long trigger;
    unsigned long _cnt;
} taskCountTriggerCore;
void taskCountTriggerRun(taskCountTriggerCore *task) large reentrant;
#endif

#if __STC_LIB_Task_USE_TaskDuoTrigger
typedef struct
{
    void (*task1)(void);
    void (*task2)(void);
    unsigned long trigger1;
    unsigned long trigger1_2;
    unsigned long _cnt;
} taskDuoTriggerCore;
void taskDuoTriggerRun(taskDuoTriggerCore *task) large reentrant;
#endif

// typedef struct
// {
//     unsigned long trigger;
//     unsigned long _cnt;
//     char flg;
// } countFlag;
// void countFlagRun(countFlag *flag) large reentrant;

#if __STC_LIB_Task_USE_TaskMsPeriodic
typedef struct
{
    sysTime_t _t;
    unsigned int _gap;
    void (*task)(void);
} taskMsPeriodicCore;
void taskMsPeriodicInit(taskMsPeriodicCore *task, unsigned int ms, void (*taskFunc)(void));
void taskMsPeriodicRun(taskMsPeriodicCore *task);
#endif

#if __STC_LIB_Task_USE_TaskMsDelay
typedef struct
{
    sysTime_t _t;
    unsigned int _gap;
    unsigned char _state;
    void (*task)(void);
} taskMsDelayCore;
void taskMsDelayInit(taskMsDelayCore *task, unsigned int ms, void (*taskFunc)(void));
void taskMsDelayStartTask(taskMsDelayCore *task);
void taskMsDelayRun(taskMsDelayCore *task);
#endif

#endif /* __STC_LIB_TASK_H__ */
