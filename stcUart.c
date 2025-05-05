#include "stcChip.h"
#include "stcUart.h"
#define __UART_NUM 4

typedef struct
{
    unsigned char isBusy : 1;
    unsigned char buffer : 7;
} UartState;

#define __UART_QUEUE_ARRAY_SIZE 10

unsigned char xdata __uartQueue[__UART_NUM][__UART_QUEUE_ARRAY_SIZE];
unsigned char xdata __uartQueueFront[__UART_NUM] = {0};
UartState xdata __uartStates[__UART_NUM] = {0};

unsigned char __uartQueuePop(unsigned char n_minus1)
{
    --__uartStates[n_minus1].buffer;
    if (__uartQueueFront[n_minus1] + 1 < __UART_QUEUE_ARRAY_SIZE)
        return __uartQueue[n_minus1][__uartQueueFront[n_minus1]++];
    __uartQueueFront[n_minus1] = 0;
    return __uartQueue[n_minus1][__UART_QUEUE_ARRAY_SIZE - 1];
}

void __uartQueuePush(unsigned char n_minus1, unsigned char d)
{
    if (__uartQueueFront[n_minus1] + __uartStates[n_minus1].buffer >= __UART_QUEUE_ARRAY_SIZE)
        __uartQueue[n_minus1][__uartQueueFront[n_minus1] + __uartStates[n_minus1].buffer - __UART_QUEUE_ARRAY_SIZE] = d;
    else
        __uartQueue[n_minus1][__uartQueueFront[n_minus1] + __uartStates[n_minus1].buffer] = d;
    ++__uartStates[n_minus1].buffer;
    if (__uartStates[n_minus1].buffer > __UART_QUEUE_ARRAY_SIZE)
        __uartQueuePop(n_minus1);
}

void (*__uartRxCallbacks[__UART_NUM])(unsigned char);

#define S1BUF SBUF
#define S1CON SCON

#define __UART_IRQ_WORK(_N)                        \
    if (S##_N##CON & 0x02)                         \
    {                                              \
        S##_N##CON &= ~0x02;                       \
        __uartStates[_N - 1].isBusy = 0;           \
    }                                              \
    if (S##_N##CON & 0x01)                         \
    {                                              \
        S##_N##CON &= ~0x01;                       \
        if (__uartRxCallbacks[_N - 1])             \
            __uartRxCallbacks[_N - 1](S##_N##BUF); \
        else                                       \
            __uartQueuePush(_N - 1, S##_N##BUF);   \
    }

#if __STC_LIB_UART_USE_uart1
void UART1IRQ_handler(void) STC_Interrupt(STC_InterruptNumUART1) { __UART_IRQ_WORK(1) }
#endif
#if __STC_LIB_UART_USE_uart2
void UART2IRQ_handler(void) STC_Interrupt(STC_InterruptNumUART2) { __UART_IRQ_WORK(2) }
#endif
#if __STC_LIB_UART_USE_uart3
void UART3IRQ_handler(void) STC_Interrupt(STC_InterruptNumUART3) { __UART_IRQ_WORK(3) }
#endif
#if __STC_LIB_UART_USE_uart4
void UART4IRQ_handler(void) STC_Interrupt(STC_InterruptNumUART4) { __UART_IRQ_WORK(4) }
#endif

#define __UART_SEND_SWITCH_CASE(_N) \
    case _N:                        \
        S##_N##BUF = d;             \
        break

void uartSendByte(unsigned char uartNum, unsigned char d)
{
    while (__uartStates[uartNum - 1].isBusy)
        ;
    __uartStates[uartNum - 1].isBusy = 1;

    switch (uartNum)
    {
        __UART_SEND_SWITCH_CASE(1);
        __UART_SEND_SWITCH_CASE(2);
        __UART_SEND_SWITCH_CASE(3);
        __UART_SEND_SWITCH_CASE(4);
    default:
        break;
    }
}

#if __STC_LIB_UART_USE_uartSendData
void uartSendData(unsigned char uartNum, unsigned char *d, unsigned char len)
{
    while (len--)
        uartSendByte(uartNum, *d++);
}
#endif
#if __STC_LIB_UART_USE_uartSendStr
void uartSendStr(unsigned char uartNum, char *s)
{
    while (*s)
        uartSendByte(uartNum, *s++);
}
#endif

char xdata __uartStack[10];
unsigned char xdata __uartStackCnt = 0;

#define __UART_STACK_PUSH(_D) __uartStack[__uartStackCnt++] = _D
#define __UART_STACK_POP() __uartStack[--__uartStackCnt]
#define __UART_STACK_Not_Empty() __uartStackCnt
// #define __UART_TOP()

#if __STC_LIB_UART_USE_uartSendHexByteNum
void uartSendHexByteNum(unsigned char uartNum, unsigned char n)
{
    unsigned char tmp;
    tmp = n >> 4;
    tmp &= 0x0f;
    if (tmp < 10)
        tmp += '0';
    else
        tmp += 55; // ('A' - 10);
    uartSendByte(uartNum, tmp);

    tmp = n & 0x0f;
    if (tmp < 10)
        tmp += '0';
    else
        tmp += 55; // ('A' - 10);
    uartSendByte(uartNum, tmp);
}
#endif

#if __STC_LIB_UART_USE_uartSendNum
void uartSendNum(unsigned char uartNum, int n)
{
    if (n < 0)
    {
        uartSendByte(uartNum, '-');
        n = -n;
    }

    while (n >= 10)
    {
        __UART_STACK_PUSH((n % 10) + '0');
        n /= 10;
    }
    uartSendByte(uartNum, n + '0');
    while (__UART_STACK_Not_Empty())
        uartSendByte(uartNum, __UART_STACK_POP());
}
#endif

#if __STC_LIB_UART_USE_uartSendFloat
void uartSendFloat(unsigned char uartNum, float n, unsigned char fmt)
{
    int intPart = n;

    uartSendNum(uartNum, intPart);
    n -= intPart;
    while (fmt--)
        n *= 10;
    intPart = n;
    if (intPart < 0)
        intPart = -intPart;
    uartSendNum(uartNum, intPart);
}
#endif
#if __STC_LIB_UART_USE_uartBufferIsNotEmpty
char uartBufferIsNotEmpty(unsigned char uartNum) { return __uartStates[uartNum - 1].buffer; }
#endif
#if __STC_LIB_UART_USE_uartGetBuffer
unsigned char uartGetBuffer(unsigned char uartNum) { return __uartQueuePop(uartNum - 1); }
#endif
#if __STC_LIB_UART_USE_uartSetRxCallback
void uartSetRxCallback(unsigned char uartNum, void (*f)(unsigned char)) { __uartRxCallbacks[uartNum - 1] = f; }
#endif
