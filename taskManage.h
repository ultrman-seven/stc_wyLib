#ifndef __STC_LIB_TASK_H__
#define __STC_LIB_TASK_H__

#include "stcSys.h"

typedef struct
{
    void (*task)(void);
    unsigned long trigger;
    unsigned long _cnt;
} taskCountTriggerCore;

typedef struct
{
    void (*task1)(void);
    void (*task2)(void);
    unsigned long trigger1;
    unsigned long trigger1_2;
    unsigned long _cnt;
} taskDuoTriggerCore;

typedef struct
{
    unsigned long trigger;
    unsigned long _cnt;
    char flg;
} countFlag;

typedef struct
{
    sysTime_t _t;
    unsigned int _gap;
    void (*task)(void);
} taskMsPeriodicCore;


void taskMsPeriodicInit(taskMsPeriodicCore *task, unsigned int ms, void (*taskFunc)(void));
void taskMsPeriodicRun(taskMsPeriodicCore *task);

void taskCountTriggerRun(taskCountTriggerCore *task) large reentrant;
void countFlagRun(countFlag *flag) large reentrant;

void taskDuoTriggerRun(taskDuoTriggerCore *task) large reentrant;


#endif /* __STC_LIB_TASK_H__ */
