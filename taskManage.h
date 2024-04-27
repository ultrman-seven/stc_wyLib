#ifndef __STC_LIB_TASK_H__
#define __STC_LIB_TASK_H__

typedef struct
{
    void (*task)(void);
    unsigned long trigger;
    unsigned long _cnt;
}countTask;

void countTaskRun(countTask *task);

#endif /* __STC_LIB_TASK_H__ */
