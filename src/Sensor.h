#ifndef _SENSOR_H
#define _SENSOR_H 1

#include "boardUtil.h"

extern volatile uint32_t SonarRightDistance;

void initializeRightSonar(void);
void initializeCenterSonar(void);
void updateRightSonar(void);
uint32_t readCenterSonar(void);
#define readRightSonar(void) (SonarRightDistance)

#endif
