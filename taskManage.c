#include "taskManage.h"
#include "string.h"

#if __STC_LIB_Task_USE_TaskCountTrigger
void countTaskRun(taskCountTriggerCore *task) large reentrant
{
    if (++task->_cnt >= task->trigger)
    {
        task->_cnt = 0;
        task->task();
    }
}
#endif

#if __STC_LIB_Task_USE_TaskDuoTrigger
void taskDuoTriggerRun(taskDuoTriggerCore *task) large reentrant
{
    if (++(task->_cnt) >= task->trigger1_2)
    {
        task->_cnt = 0;
        task->task2();
    }
    else if (task->_cnt >= task->trigger1)
        task->task1();
}
#endif

// void countFlagRun(countFlag *flag) large reentrant
// {
//     if (++flag->_cnt >= flag->trigger)
//     {
//         flag->_cnt = 0;
//         flag->flg = 1;
//     }
// }

#if __STC_LIB_Task_USE_TaskMsPeriodic
void taskMsPeriodicInit(taskMsPeriodicCore *task, unsigned int ms, void (*taskFunc)(void))
{
    task->_gap = ms;
    task->task = taskFunc;
    sysGetTimeStamp(&task->_t);
}

void taskMsPeriodicRun(taskMsPeriodicCore *core)
{
    sysTime_t xdata t;
    sysGetTimeStamp(&t);
    if (sysTimeMinusMs(&core->_t, &t) >= core->_gap)
    {
        core->task();
        memcpy(&core->_t, &t, sizeof(sysTime_t));
    }
}
#endif

#if __STC_LIB_Task_USE_TaskMsDelay
typedef enum
{
    taskMsDelayStateIdle = 0,
    taskMsDelayStateRunning,
} taskMsDelayFmsState_t;

void taskMsDelayInit(taskMsDelayCore *task, unsigned int ms, void (*taskFunc)(void))
{
    task->_gap = ms;
    task->task = taskFunc;
    task->_state = taskMsDelayStateIdle;
}

void taskMsDelayStartTask(taskMsDelayCore *task)
{
    if (task->_state != taskMsDelayStateIdle)
        return;
    task->_state = taskMsDelayStateRunning;
    sysGetTimeStamp(&task->_t);
}

void taskMsDelayRun(taskMsDelayCore *task)
{
    if (task->_state == taskMsDelayStateRunning)
    {
        sysTime_t xdata t;
        sysGetTimeStamp(&t);
        if (sysTimeMinusMs(&task->_t, &t) >= task->_gap)
        {
            task->task();
            task->_state = taskMsDelayStateIdle;
        }
    }
}

#endif
