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

/**
 * Waits for the given number of milliseconds
 * DO NOT CALL THIS FROM SYSTICK
 * You probably shouldn't call this from any other interrupts either since it's a wait.
 */
void wait(int millis) {
	int stopTime = Time + (millis * TICKS_PER_SECOND)/1000;
	while(Time - stopTime < 0);
}
