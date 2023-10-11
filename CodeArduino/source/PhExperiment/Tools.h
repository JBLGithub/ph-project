#include <Arduino.h>

#ifndef TOOLS_H
#define TOOLS_H
float GetAvgRange(float arr[], int arrSize);
void SortArray(float arr[], int arrSize);
void Swap(float* xp, float* yp);
float RoundResult(float i);
void PrintArray(float arr[]);
#endif
