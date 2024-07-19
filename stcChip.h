#ifndef __STC_LIB_CHIP_H___WhatWouldHappenIf_LOVE_WasLike_A_MicroController__
#define __STC_LIB_CHIP_H___WhatWouldHappenIf_LOVE_WasLike_A_MicroController__

#include "stcInterruptNum.h"

#if defined _ChipSTC8G
#include "STC8G.H"
#elif defined _ChipSTC8H
#include "STC8H.H"
#else
// #include "reg52.h"
#error No Chip Define
#endif

#ifndef ChipSysClkFreq
#define ChipSysClkFreq 12
#endif

#define StateDisable
#define StateEnable
#define IRQ_Set(_state) EA = _state
#define IRQ_Disable() EA = 0
#define IRQ_Enable() EA = 1

#endif /* __STC_LIB_CHIP_H___WhatWouldHappenIf_LOVE_WasLike_A_MicroController__ */
