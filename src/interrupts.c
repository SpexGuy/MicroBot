#include "interrupts.h"
#include "Indicator.h"

 /****************************************************************************
 * The SysTick Handler 
 *
 * Register Information on the SysTick timer can be found on pages 129-132 
 * of the MCU data sheet.
 *
 * Register Information on the Watchdog timer can be found on pages 749-754.
 *
 ****************************************************************************/

#define ADC_RATE 200
#define PRINT_RATE TICKS_PER_SECOND

#define MAX_NUM_TASKS 64

int numTasks = 0;
struct {
	void (*run)(void *);
	void *param;
} systickTasks[MAX_NUM_TASKS];

static void runVoidFunctor(void *param) {
	((void (*)(void))param)();
}

int addSystickTask(void (*run)(void *), void *param) {
	if (numTasks < MAX_NUM_TASKS) {
		systickTasks[numTasks].run = run;
		systickTasks[numTasks].param = param;
		numTasks++;
		return 0;
	} else {
		printf("ERROR! too many systick tasks!\r\n");
		return -1;
	}
}

int addVoidSystickTask(void (*run)(void)) {
	return addSystickTask(runVoidFunctor, run);
}


volatile bool CheckADC = false;
volatile bool PrintVals = false;
volatile int Time = 0;

static Indicator systickIndicator;

void initializeSysTick(int micros) {
	SysTick_Config(SystemCoreClock * micros / 1000000);
	createIndicator(&systickIndicator, SYSTICK_INDICATOR);
	addSystickTask((void (*)(void *))&triggerIndicator, &systickIndicator);
}

void SysTick_Handler(void)
{
	int c;
	Time++;
	for (c = 0; c < numTasks; c++) {
		systickTasks[c].run(systickTasks[c].param);
	}
}
