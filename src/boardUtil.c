#include "TM4C123GH6PM.h"
#include "boardUtil.h"
#include "interrupts.h"

void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

//*****************************************************************************
//*****************************************************************************
void serialDebugInit(void)
{
  
  UART_CONFIG serialDebugConfig = {
    SERIAL_DEBUG_UART_BASE,
    ENABLED,                    // UART
    ENABLED,                    // UARTRx
    ENABLED,                    // UARTTx
    _8BITS,                     // WordLen
    9600,                       // BaudRate
    ENABLED,                    // FIFO
    DISABLED,                   // _2Stop
    DISABLED,                   // Parity
    DISABLED,                   // EvenParity
    DISABLED,                   // HighSpeed
    RX_ONE_EIGHTH,              // RxIntFIFO
    TX_ONE_EIGHTH,              // TxIntFIFO
    ENABLED,                    // RxIntMask
    ENABLED,                    // TxIntMask
    ENABLED,                    // RxTimeOutIntMask
    DISABLED,                   // OvrrIntMask
    DISABLED,                   // ParityErrIntMask
    DISABLED                    // FramingErrIntMask  
  };
  
  // Configure Rx Pins
  gpioConfigDigitalEnable(SERIAL_DBG_BASE, SERIAL_DBG_RX_PIN);
  gpioConfigAltFunction(SERIAL_DBG_BASE, SERIAL_DBG_RX_PIN);
  gpioConfigPortConfig(SERIAL_DBG_BASE, SERIAL_DBG_RX_PCTL);
  
  // Configure Tx Pins
  gpioConfigDigitalEnable(SERIAL_DBG_BASE, SERIAL_DBG_TX_PIN);
  gpioConfigAltFunction(SERIAL_DBG_BASE, SERIAL_DBG_TX_PIN);
  gpioConfigPortConfig(SERIAL_DBG_BASE, SERIAL_DBG_TX_PCTL);
  
  // Initialize UART0 for serial debug
  InitializeUART(&serialDebugConfig);
}

void initializeRightSonar(void) {
	validatePortIsOn(SONAR_RIGHT_BASE);
	gpioConfigDigitalEnable(SONAR_RIGHT_BASE, SONAR_RIGHT_PIN);
	gpioConfigPinAsInput(SONAR_RIGHT_BASE, SONAR_RIGHT_PIN);
}

volatile int SonarRightDistance = 0;
void updateRightSonar(void) {
	static bool lastSonarVal = false;
	static int sonarCount = 0;
	bool sonarVal = SONAR_RIGHT_VALUE;
	if (sonarVal != lastSonarVal) {
		if (sonarVal) {
			sonarCount = 0;
		} else {
			SonarRightDistance = (sonarCount * TIME_QUANTUM_MICROS) / SONAR_RIGHT_MICROS_PER_INCH;
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

void initializeSysTick(int micros) {
	SysTick_Config(SystemCoreClock * micros / 1000000);
	createIndicator(&systickIndicator, SYSTICK_INDICATOR);
}

//void initializeIndicator(uint32_t base, uint32_t port) {
//	validatePortIsOn(base);
//	gpioConfigDigitalEnable(base, port);
//	gpioConfigPinAsOutput(base, port);
//}
