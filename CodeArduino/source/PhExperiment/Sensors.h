#ifndef SENSORS_H
#define SENSORS_H

//InLibraries
#include "Relays.h"
#include "Tools.h"

//OutLibraries
#include <Arduino.h>
#include "DFRobot_EC.h"
#include "DFRobot_PH.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Class
class Sensors
{
  private:
    int TEMP_PIN;
    int EC_PIN;
    int PH_PIN;

    OneWire oneWire;
    DallasTemperature tempSensor;
    DeviceAddress deviceAddress;
    DFRobot_EC ec;
    DFRobot_PH ph;
    
  public:
    Sensors(int ecpin, int phpin, int temppin);
    void SetupTemperatureProbe();
    void SetupECSensor();
    void SetupPHSensor();
    void CalibratePH();

    float GetAverageTemp();
    float GetAverageEC();
    float GetAveragePH();
};

#endif
