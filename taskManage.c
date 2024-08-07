#include "taskManage.h"

void countTaskRun(countTask *task) large reentrant
{
    if (++task->_cnt >= task->trigger)
    {
        task->_cnt = 0;
        task->task();
    }
}

void taskDuoTriggerRun(taskDuoTrigger *task) large reentrant
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
