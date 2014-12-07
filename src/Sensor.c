#include "Sensor.h"
#include "interrupts.h"

void initializeRightSonar(void) {
	validatePortIsOn(SONAR_RIGHT_BASE);
	gpioConfigDigitalEnable(SONAR_RIGHT_BASE, SONAR_RIGHT_PIN);
	gpioConfigPinAsInput(SONAR_RIGHT_BASE, SONAR_RIGHT_PIN);
	addVoidSystickTask(&updateRightSonar);
}

volatile uint32_t SonarRightDistance = 0;
void updateRightSonar(void) {
	static bool lastSonarVal = false;
	static int sonarCount = 0;
	bool sonarVal = SONAR_RIGHT_VALUE;
	if (sonarVal != lastSonarVal) {
		if (sonarVal) {
			sonarCount = 0;
		} else {
			SonarRightDistance = (sonarCount * MICROS_PER_TICK) / SONAR_RIGHT_MICROS_PER_INCH;
		}
	} else {
		sonarCount++;
	}
	lastSonarVal = sonarVal;
}

void initializeCenterSonar(void) {
	validatePortIsOn(SONAR_CENTER_BASE);
	gpioConfigAnalogEnable(SONAR_CENTER_BASE, SONAR_CENTER_PIN);
	gpioConfigPinAsInput(SONAR_CENTER_BASE, SONAR_CENTER_PIN);
	gpioConfigAltFunction(SONAR_CENTER_BASE, SONAR_CENTER_PIN);
	initializeADC(SONAR_CENTER_ADC_BASE);
}

uint32_t readCenterSonar(void) {
	return (getADCValue(SONAR_CENTER_ADC_BASE, SONAR_CENTER_ADC_CHANNEL) * SONAR_MICROV_PER_UNIT) / SONAR_CENTER_MICROV_PER_INCH;
}

