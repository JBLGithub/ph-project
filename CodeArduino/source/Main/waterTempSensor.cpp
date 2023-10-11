#include "waterTempSensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define TempPin 2

OneWire oneWire(TempPin);
DallasTemperature sensors(&oneWire);

DeviceAddress deviceAddress;
void setupWaterTemp()
{

  Serial.println("***************************");
  Serial.print("Temperature probe setup started...");
  
  //Begin
  sensors.begin();

  //Check for sensor
  if(sensors.getDeviceCount() < 1){
    Serial.println("Failed to find water probe");
    Serial.println("***************************");
    return;
  }

  // report parasite power requirements
  Serial.print("Parasite power is: "); 
  if (sensors.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");

  if(!sensors.getAddress(deviceAddress, 0))
  {
    Serial.print("Found ghost device but could not detect address - Check power and cabling");
    Serial.println("***************************");
    return;
  }
  else 
  {
    Serial.println("Found device...");
    sensors.setResolution(deviceAddress, 12); //lowest resolution
    Serial.print("Resolution set to ");
    Serial.print(sensors.getResolution(deviceAddress), DEC);
    Serial.println();
    Serial.println("Setup Success");
    Serial.println("***************************");
  }
}

float currentWaterTemp(){
  sensors.requestTemperatures();  
  return sensors.getTempC(deviceAddress);
}
