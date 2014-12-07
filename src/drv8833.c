#include "drv8833.h"
#include "boardUtil.h"

#define PWM_LOAD_VAL    10000
#define PWM_CHANNEL_PWM_A (PWM_GEN_ACTCMPAD_LOW | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_PWM_B (PWM_GEN_ACTCMPBD_LOW | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_LOW   (PWM_GEN_ACTCMPBD_LOW | PWM_GEN_ACTLOAD_LOW | PWM_GEN_ACTZERO_NOTHING)
#define PWM_CHANNEL_HIGH  (PWM_GEN_ACTCMPBD_HIGH | PWM_GEN_ACTLOAD_HIGH | PWM_GEN_ACTZERO_NOTHING)

#define LEFT_MOTOR				PWM0_BASE, 1
#define LEFT_FORWARDS			PWM_CHANNEL_PWM_A, PWM_CHANNEL_LOW
#define LEFT_BACKWARDS		PWM_CHANNEL_LOW, PWM_CHANNEL_PWM_B
#define LEFT_STOP					PWM_CHANNEL_LOW, PWM_CHANNEL_LOW
#define RIGHT_MOTOR				PWM1_BASE, 1
#define RIGHT_FORWARDS		LEFT_FORWARDS
#define RIGHT_BACKWARDS		LEFT_BACKWARDS
#define RIGHT_STOP				PWM_CHANNEL_LOW, PWM_CHANNEL_LOW


//*****************************************************************************
// Initializes the 6 pins needed to control the DRV8833
//*****************************************************************************
void  drv8833_gpioInit(void)
{
	SYSCTL->RCGCPWM |= 3;
	//SYSCTL->RCC |= SYSCTL_RCC_USEPWMDIV;
	//SYSCTL->RCC |= SYSCTL_RCC_PWMDIV_2;

	validatePortIsOn(MOTOR_FAULT_BASE);
	gpioConfigDigitalEnable(MOTOR_FAULT);
	gpioConfigPinAsInput(MOTOR_FAULT);
	
	validatePortIsOn(MOTOR_SLEEP_BASE);
	gpioConfigDigitalEnable(MOTOR_SLEEP);
	gpioConfigPinAsOutput(MOTOR_SLEEP);
	
	validatePortIsOn(LEFT_MOTOR_BASE);
	gpioConfigDigitalEnable(LEFT_MOTOR_FORWARD);
	gpioConfigAltFunction(LEFT_MOTOR_FORWARD);
	gpioConfigPinAsOutput(LEFT_MOTOR_FORWARD);
	
	gpioConfigDigitalEnable(LEFT_MOTOR_BACKWARD);
	gpioConfigAltFunction(LEFT_MOTOR_BACKWARD);
	gpioConfigPinAsOutput(LEFT_MOTOR_BACKWARD);
	
	gpioConfigPortConfig(LEFT_MOTOR_BASE, LEFT_MOTOR_PCNTL);

	validatePortIsOn(RIGHT_MOTOR_BASE);
	
	gpioConfigDigitalEnable(RIGHT_MOTOR_FORWARD);
	gpioConfigAltFunction(RIGHT_MOTOR_FORWARD);
	gpioConfigPinAsOutput(RIGHT_MOTOR_FORWARD);
	
	gpioConfigDigitalEnable(RIGHT_MOTOR_BACKWARD);
	gpioConfigAltFunction(RIGHT_MOTOR_BACKWARD);
	gpioConfigPinAsOutput(RIGHT_MOTOR_BACKWARD);
	
	gpioConfigPortConfig(RIGHT_MOTOR_BASE, RIGHT_MOTOR_PCNTL);
	
	GPIOF->DATA |= MOTOR_SLEEP_PORT; // turn off motor sleep
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftForward(uint8_t dutyCycle)
{
	if (dutyCycle) {
		uint32_t gen = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(LEFT_MOTOR, PWM_LOAD_VAL, gen, gen, LEFT_FORWARDS);
	} else {
		drv8833_stop();
	}
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_leftReverse(uint8_t dutyCycle)
{
	if (dutyCycle) {
		uint32_t gen = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(LEFT_MOTOR, PWM_LOAD_VAL, gen, gen, LEFT_BACKWARDS);
	} else {
		drv8833_stop();
	}
}


//*****************************************************************************
//*****************************************************************************
void  drv8833_rightForward(uint8_t dutyCycle)
{
	if (dutyCycle) {
		uint32_t gen = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(RIGHT_MOTOR, PWM_LOAD_VAL, gen, gen, RIGHT_FORWARDS);
	} else {
		drv8833_stop();
	}
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_rightReverse(uint8_t dutyCycle)
{
	if (dutyCycle) {
		uint32_t gen = (PWM_LOAD_VAL * (100-dutyCycle))/100;
		pwmConfig(RIGHT_MOTOR, PWM_LOAD_VAL, gen, gen, RIGHT_BACKWARDS);
	} else {
		drv8833_stop();
	}
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_forward(uint8_t dutyCycle)
{
	drv8833_rightForward(dutyCycle);
	drv8833_leftForward(dutyCycle);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_reverse(uint8_t dutyCycle)
{
	drv8833_rightReverse(dutyCycle);
	drv8833_leftReverse(dutyCycle);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnLeft(uint8_t dutyCycle)
{
	drv8833_rightForward(dutyCycle);
	drv8833_leftReverse(dutyCycle);
}

//*****************************************************************************
//*****************************************************************************
void  drv8833_turnRight(uint8_t dutyCycle)
{
	drv8833_rightReverse(dutyCycle);
	drv8833_leftForward(dutyCycle);
}

void	drv8833_stop()
{
  pwmConfig(LEFT_MOTOR, PWM_LOAD_VAL, 0, 0, LEFT_STOP);
  pwmConfig(RIGHT_MOTOR, PWM_LOAD_VAL, 0, 0, RIGHT_STOP);
}
