#ifndef __STC_LIB_TASK_H__
#define __STC_LIB_TASK_H__

typedef struct
{
    void (*task)(void);
    unsigned long trigger;
    unsigned long _cnt;
} countTask;

typedef struct
{
    void (*task1)(void);
    void (*task2)(void);
    unsigned long trigger1;
    unsigned long trigger1_2;
    unsigned long _cnt;
} taskDuoTrigger;

typedef struct
{
    unsigned long trigger;
    unsigned long _cnt;
    char flg;
} countFlag;

void countTaskRun(countTask *task) large reentrant;
void countFlagRun(countFlag *flag) large reentrant;

void taskDuoTriggerRun(taskDuoTrigger *task) large reentrant;

#define taskCountTrigger countTask
#define taskCountTriggerRun countTaskRun

#endif /* __STC_LIB_TASK_H__ */
