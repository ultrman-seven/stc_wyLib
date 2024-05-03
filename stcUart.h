#ifndef __WY_STC_LIB__UART_H__
#define __WY_STC_LIB__UART_H__
#include "stcChip.h"

void uartSendByte(unsigned char uartNum, unsigned char d);
void uartSendData(unsigned char uartNum, unsigned char *d, unsigned char len);
void uartSendStr(unsigned char uartNum, char *s);
void uartSendNum(unsigned char uartNum, int n);
void uartSendFloat(unsigned char uartNum, float n, unsigned char fmt);
char uartBufferIsNotEmpty(unsigned char uartNum);
unsigned char uartGetBuffer(unsigned char uartNum);
void uartSetRxCallback(unsigned char uartNum, void (*f)(unsigned char));

#define __UART1_IRQ_EN ES = 1
#define __UART2_IRQ_EN IE2 |= 0x01
#define __UART3_IRQ_EN IE2 |= 0x08
#define __UART4_IRQ_EN IE2 |= 0x10

#define uartIQR_Enable(_uartx) __UART##_uartx##_IRQ_EN

#endif /* __WY_STC_LIB__UART_H__ */
