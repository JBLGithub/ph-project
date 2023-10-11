#include <Arduino.h>

#ifndef ECSENSOR_H
#define ECSENSOR_H

void setupEC();
void calibrateEC();
float currentECPPM();

#endif
