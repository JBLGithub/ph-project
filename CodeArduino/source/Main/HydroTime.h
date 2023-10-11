#include <Arduino.h>

#ifndef HYDROTIME_H
#define HYDROTIME_H
void setupTime();
void getTimeFromJson(String data);
String getTimeString();
String formatTime(int sTime);
#endif
