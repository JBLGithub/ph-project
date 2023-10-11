#include <Arduino.h>

#ifndef PHSENSOR_H
#define PHSENSOR_H
void setupPH();
void calibratePH();
float currentPH();
void printArray(float* arr);
#endif
