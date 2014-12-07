#include "Indicator.h"

void createIndicator(Indicator *indicator, uint32_t base, uint32_t port) {
	validatePortIsOn(base);
	gpioConfigDigitalEnable(base, port);
	gpioConfigPinAsOutput(base, port);
	indicator->base = base;
	indicator->port = port;
	indicator->data = &(((uint32_t *)base)[port]);
	indicator->value = false;
}

void triggerIndicator(Indicator *indicator) {
	*indicator->data = indicator->value ? 0xFF : 0;
	indicator->value = !indicator->value;
}
