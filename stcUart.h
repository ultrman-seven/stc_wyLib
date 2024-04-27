#ifndef __WY_STC_LIB__UART_H__
#define __WY_STC_LIB__UART_H__
void uartSendByte(unsigned char uartNum, unsigned char d);
void uartSendData(unsigned char uartNum, unsigned char *d, unsigned char len);
void uartSendStr(unsigned char uartNum, char *s);
void uartSendNum(unsigned char uartNum, int n);
void uartSendFloat(unsigned char uartNum, float n, unsigned char fmt);
char uartBufferIsNotEmpty(unsigned char uartNum);
unsigned char uartGetBuffer(unsigned char uartNum);
void uartSetRxCallback(unsigned char uartNum, void (*f)(unsigned char));
#endif /* __WY_STC_LIB__UART_H__ */
