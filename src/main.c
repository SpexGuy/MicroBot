//*****************************************************************************
// main.c
// Author: jkrachey@wisc.edu
//*****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "boardUtil.h"
#include "interrupts.h"
#include "Indicator.h"

#define FW_VERSION  "0.0.1"

/******************************************************************************
 * Global Variables
 *****************************************************************************/


//*****************************************************************************
//*****************************************************************************
void initializeBoard(void)
{
  
  DisableInterrupts();
  
  serialDebugInit();
	initializeSysTick(TIME_QUANTUM_MICROS);
	initializeRightSonar();
	initializeCenterSonar();
	//initializeIndicator(MAIN_INDICATOR);
	

  EnableInterrupts();
  
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	//static bool clk_val = true;
	Indicator indicator;
	uint32_t centerVal;
  initializeBoard();
	createIndicator(&indicator, MAIN_INDICATOR);

  printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE315 Base Project                 \n\r");
  printf("* FW Version:%s\n\r",FW_VERSION);
  printf("**************************************\n\r");
  
  // Infinite Loop
  while(1)
  {
		if (CheckADC) {
			CheckADC = false;
			//clk_val = !clk_val;
			triggerIndicator(&indicator);
			//setMainIndicator(clk_val);
			
			centerVal = readCenterSonar();
			//printf("%d\n", readCenterSonar());
		}
		if (PrintVals) {
			PrintVals = false;
			printf("Center: %3d Right: %3d\n", centerVal, SonarRightDistance);
		}
  }
}
