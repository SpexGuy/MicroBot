
#include "interrupts.h"


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
#define PRINT_RATE (1000000/TIME_QUANTUM_MICROS)

volatile bool CheckADC = false;
volatile bool PrintVals = false;
volatile int Time = 0;

Indicator systickIndicator;

void SysTick_Handler(void)
{
	//static bool indicatorValue = false;
	//indicatorValue = !indicatorValue;
	//setSystickIndicator(indicatorValue);
	triggerIndicator(&systickIndicator);
	Time++;
	CheckADC |= (Time % ADC_RATE == 0);
	PrintVals |= (Time % PRINT_RATE == 0);
	updateRightSonar();
	
}
