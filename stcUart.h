#ifndef __WY_STC_LIB__UART_H__
#define __WY_STC_LIB__UART_H__
#include "stcChip.h"

#if __STC_LIB_UART_USE_uartSendHexByteNum
void uartSendHexByteNum(unsigned char uartNum, unsigned char n);
#endif

#if __STC_LIB_UART_USE_uartSendByte
void uartSendByte(unsigned char uartNum, unsigned char d);
#endif

#if __STC_LIB_UART_USE_uartSendData
void uartSendData(unsigned char uartNum, unsigned char *d, unsigned char len);
#endif

#if __STC_LIB_UART_USE_uartSendStr
void uartSendStr(unsigned char uartNum, char *s);
#endif

#if __STC_LIB_UART_USE_uartSendNum
void uartSendNum(unsigned char uartNum, int n);
#endif

#if __STC_LIB_UART_USE_uartSendFloat
void uartSendFloat(unsigned char uartNum, float n, unsigned char fmt);
#endif

#if __STC_LIB_UART_USE_uartBufferIsNotEmpty
char uartBufferIsNotEmpty(unsigned char uartNum);
#endif

#if __STC_LIB_UART_USE_uartGetBuffer
unsigned char uartGetBuffer(unsigned char uartNum);
#endif

#if __STC_LIB_UART_USE_uartSetRxCallback
void uartSetRxCallback(unsigned char uartNum, void (*f)(unsigned char));
#endif

#define __UART1_IRQ_EN ES = 1
#define __UART2_IRQ_EN IE2 |= 0x01
#define __UART3_IRQ_EN IE2 |= 0x08
#define __UART4_IRQ_EN IE2 |= 0x10

#define uartIQR_Enable(_uartx) __UART##_uartx##_IRQ_EN

#endif /* __WY_STC_LIB__UART_H__ */
