#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>
#include <stdbool.h>

#include "TM4C123.h"
#include "boardUtil.h"
#include "Indicator.h"

#define TIME_QUANTUM_MICROS 50

extern volatile int Time;
extern volatile bool CheckADC;
extern volatile bool PrintVals;
extern Indicator systickIndicator;

void TIMER0A_Handler(void);
void SysTick_Handler(void);
void GPIOE_Handler(void);

#endif
