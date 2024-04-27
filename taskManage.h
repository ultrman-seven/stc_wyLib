#ifndef E7ECD4E5_609C_4FC4_9059_031399811A70
#define E7ECD4E5_609C_4FC4_9059_031399811A70

typedef struct
{
    void (*task)(void);
    unsigned long trigger;
    unsigned long _cnt;
}countTask;

void countTaskRun(countTask *task);

#endif /* E7ECD4E5_609C_4FC4_9059_031399811A70 */
