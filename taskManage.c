#include "taskManage.h"
#include "string.h"

void countTaskRun(taskCountTriggerCore *task) large reentrant
{
    if (++task->_cnt >= task->trigger)
    {
        task->_cnt = 0;
        task->task();
    }
}

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

void countFlagRun(countFlag *flag) large reentrant
{
    if (++flag->_cnt >= flag->trigger)
    {
        flag->_cnt = 0;
        flag->flg = 1;
    }
}

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
