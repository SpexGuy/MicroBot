#ifndef __INTERRUPTS_H__
#define __INTERRUPTS_H__

#include <stdint.h>
#include <stdbool.h>

#include "TM4C123.h"
#include "boardUtil.h"

#define MICROS_PER_TICK 50
#define TICKS_PER_SECOND (1000000/MICROS_PER_TICK)

extern volatile int Time;

int addSystickTask(void (*run)(void *), void *param);
int addVoidSystickTask(void (*run)(void));

void initializeSysTick(int micros);
void SysTick_Handler(void);

void TIMER0A_Handler(void);
void GPIOE_Handler(void);

#endif
