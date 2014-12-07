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
#include "drv8833.h"

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
	initializeSysTick(MICROS_PER_TICK);
	drv8833_gpioInit();

  EnableInterrupts();
}


//*****************************************************************************
//*****************************************************************************
int 
main(void)
{
	initializeBoard();

  printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE315 Base Project                 \n\r");
  printf("* FW Version:%s\n\r",FW_VERSION);
  printf("**************************************\n\r");
	
	drv8833_forward(100);
	wait(2000);
	drv8833_reverse(100);
	wait(2000);
	drv8833_turnLeft(100);
	wait(5000);
	drv8833_turnRight(100);
	wait(5000);
	drv8833_stop();
	while(1);
}
