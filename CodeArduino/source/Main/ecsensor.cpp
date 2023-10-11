#include "ecsensor.h"
#include "waterTempSensor.h"
#include "DFRobot_EC.h"
#include <EEPROM.h>

#define EC_PIN A1

DFRobot_EC ec;
void setupEC()
{ 
  ec.begin();
}

void calibrateEC()
{
  float voltage,ecValue,temperature = 25;
  bool calibrated = false;
  while(!calibrated)
  {
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U) //time interval: 1s
    {
      timepoint = millis();
      voltage = analogRead(EC_PIN)/1024.0*4300; //read voltage
      temperature = currentWaterTemp();
      //temperature = 23.5;
      ecValue = ec.readEC(voltage,temperature);
      Serial.print("temperature:");
      Serial.print(temperature,1);
      Serial.print("^C  EC:");
      Serial.print(ecValue,2);
      Serial.println("ms/cm");   
    }
    ec.calibration(voltage,temperature);
  } 
}

float currentECPPM()
{
  float averageRange[10];
  for(int i=0; i<10; i++)
  {
    averageRange[i] = analogRead(EC_PIN)/1024.0*4300;
    delay(100);
  }

  //printArray(averageRange);
  for(int i=0; i<10; i++){
    for(int j=0; j<10-i-1; j++)
    {
      if(averageRange[j] > averageRange[j+1])
      {
        float temp = averageRange[j];
        averageRange[j] = averageRange[j+1];
        averageRange[j+1] = temp;
      }
    }
  }

  //printArray(averageRange);
  float average = 0;
  for(int i=2; i<8; i++)
  {
    average += averageRange[i];
  }
  
  float voltage = average/6.0;
  float temperature = currentWaterTemp();          
  float ecValue =  ec.readEC(voltage,temperature)*500.0; //*500 from ms to ppm
  ec.calibration(voltage,temperature);
  return ecValue;
}
