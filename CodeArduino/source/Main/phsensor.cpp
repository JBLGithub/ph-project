#define PH_PIN A0

#include "phsensor.h"
#include "waterTempSensor.h"

#include "DFRobot_PH.h"
#include <EEPROM.h>
DFRobot_PH ph;

void setupPH()
{
  ph.begin();
}

void calibratePH()
{
  float voltage, phValue, temperature = 25;
  static unsigned long timepoint = millis();
  if(millis()-timepoint>1000U){                  //time interval: 1s
      timepoint = millis();
      temperature = currentWaterTemp();         // read your temperature sensor to execute temperature compensation
      voltage = analogRead(PH_PIN)/1024.0*4300; // read the voltage
      phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
      Serial.print("temperature:");
      Serial.print(temperature,1);
      Serial.print("^C  pH:");
      Serial.println(phValue,2);
  }
  ph.calibration(voltage,temperature);
}

float currentPH()
{
  float averageRange[10];
  for(int i=0; i<10; i++)
  {
    averageRange[i] = analogRead(PH_PIN)/1024.0*4300;
    delay(100);
  }

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

  float average = 0;
  for(int i=2; i<8; i++)
  {
    average += averageRange[i];
  }
  
  float voltage = average/6.0;
  float temperature = currentWaterTemp();  
  float phvalue = ph.readPH(voltage,temperature);
  return phvalue;
}

void printArray(float* arr)
{
  for(int i=0; i<10; i++)
  {
    Serial.print(arr[i]);
    Serial.print(";");
  }
  Serial.println();
}
