#ifndef __INDICATOR_H__
#define __INDICATOR_H__

#include "../include/uart.h"
#include "../include/sysctrl.h"
#include "../include/gpio.h"
#include "../include/adc.h"

typedef struct __indicator__{
	uint32_t base;
	uint32_t port;
	volatile uint32_t *data;
	bool value;
} Indicator;

void createIndicator(Indicator *indicator, uint32_t base, uint32_t port);
void triggerIndicator(Indicator *indicator);

#endif
