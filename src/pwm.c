#include "pwm.h"



//*****************************************************************************
//*****************************************************************************
uint8_t pwmConfig(
  uint32_t base,
  uint8_t pwm_generator,
  uint32_t load,
  uint32_t cmpa,
  uint32_t cmpb,
  uint32_t gena,
  uint32_t genb
)
{
	PWM0_Type *pwm;
	uint8_t portMask;
	pwm = (PWM0_Type*)base;
	portMask = (3<<(pwm_generator<<1));
	//SYSCTL->RCC |= USEPWMDIV;

	pwm->ENABLE &= ~portMask;
	switch(pwm_generator) {
		case 0:
			pwm->_0_CTL &= ~1;
			pwm->_0_GENA = gena;
			pwm->_0_GENB = genb;
			pwm->_0_LOAD = load;
			pwm->_0_CMPA = cmpa;
			pwm->_0_CMPB = cmpb;
			pwm->_0_CTL |= 1;
			break;
		case 1:
			pwm->_1_CTL &= ~1;
			pwm->_1_GENA = gena;
			pwm->_1_GENB = genb;
			pwm->_1_LOAD = load;
			pwm->_1_CMPA = cmpa;
			pwm->_1_CMPB = cmpb;
			pwm->_1_CTL |= 1;
			break;
		case 2:
			pwm->_2_CTL &= ~1;
			pwm->_2_GENA = gena;
			pwm->_2_GENB = genb;
			pwm->_2_LOAD = load;
			pwm->_2_CMPA = cmpa;
			pwm->_2_CMPB = cmpb;
			pwm->_2_CTL |= 1;
			break;
		case 3:
			pwm->_3_CTL &= ~1;
			pwm->_3_GENA = gena;
			pwm->_3_GENB = genb;
			pwm->_3_LOAD = load;
			pwm->_3_CMPA = cmpa;
			pwm->_3_CMPB = cmpb;
			pwm->_3_CTL |= 1;
			break;
		default:
			return 0xFF;
	}
	pwm->CTL |= (1<<pwm_generator);
	pwm->ENABLE |= portMask;
  return 0;
}
