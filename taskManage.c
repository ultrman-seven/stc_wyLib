#include "taskManage.h"

void countTaskRun(countTask *task)
{
    if (++task->_cnt >= task->trigger)
    {
        task->_cnt = 0;
        task->task();
    }
}
