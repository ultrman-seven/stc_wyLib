#ifndef E7308259_4FB0_4531_8070_2FBDE4334599
#define E7308259_4FB0_4531_8070_2FBDE4334599

#ifndef __vscode__
#define STC_Interrupt(_N) interrupt _N
#else
#define STC_Interrupt(_N)
#endif

#define STC_InterruptNumTimer0 1
#define STC_InterruptNumTimer1 3
#define STC_InterruptNumTimer2 12
#define STC_InterruptNumTimer3 19
#define STC_InterruptNumTimer4 20

#define STC_InterruptNumADC 5

#define STC_InterruptNumINT0 0
#define STC_InterruptNumINT1 2
#define STC_InterruptNumINT2 10
#define STC_InterruptNumINT3 11
#define STC_InterruptNumINT4 16

#define STC_InterruptNumUART1 4
#define STC_InterruptNumUART2 8
#define STC_InterruptNumUART3 17
#define STC_InterruptNumUART4 18

#define STC_InterruptNumP0INT 37
#define STC_InterruptNumP1INT 38
#define STC_InterruptNumP2INT 39
#define STC_InterruptNumP3INT 40
#define STC_InterruptNumP4INT 41
#define STC_InterruptNumP5INT 42
#define STC_InterruptNumP6INT 43
#define STC_InterruptNumP7INT 44

#define STC_InterruptNumDMA_M2M 47  // 017BH
#define STC_InterruptNumDMA_ADC 48  // 0183H
#define STC_InterruptNumDMA_SPI 49  // 018BH
#define STC_InterruptNumDMA_UR1T 50 // 0193H
#define STC_InterruptNumDMA_UR1R 51 // 019BH
#define STC_InterruptNumDMA_UR2T 52 // 01A3H
#define STC_InterruptNumDMA_UR2R 53 // 01ABH
#define STC_InterruptNumDMA_UR3T 54 // 01B3H
#define STC_InterruptNumDMA_UR3R 55 // 01BBH
#define STC_InterruptNumDMA_UR4T 56 // 01C3H
#define STC_InterruptNumDMA_UR4R 57 // 01CBH
#define STC_InterruptNumDMA_LCM 58  // 01D3H

#define STC_InterruptNumPWM_A 26
#define STC_InterruptNumPWM_B 27
#define STC_InterruptNumPWM1 28
#define STC_InterruptNumPWM2 29
#define STC_InterruptNumPWM3 30
#define STC_InterruptNumPWM4 31
#define STC_InterruptNumPWM5 32
#define STC_InterruptNumPWM2FD 33
#define STC_InterruptNumPWM4FD 34
#define STC_InterruptNumTKSU 35 // 011BH

#define STC_InterruptNumLVD 6   // 0033H
#define STC_InterruptNumSPI 9   // 004B
#define STC_InterruptNumUSER 13 // 006BH

#define STC_InterruptNumCMP 21 // 00ABH
#define STC_InterruptNumI2C 24 // 00C3H
#define STC_InterruptNumUSB 25 // 00CBH

#endif/* E7308259_4FB0_4531_8070_2FBDE4334599 */
