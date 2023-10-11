//Header
#include "Sensors.h"

Sensors::Sensors(int ecpin, int phpin, int temppin) : oneWire(temppin), tempSensor(&oneWire)
{
  Serial.println("Sensors set up started...");
  TEMP_PIN = temppin;
  EC_PIN = ecpin;
  PH_PIN = phpin;
  Serial.println("Sensors set up completed.");
}

void Sensors::SetupTemperatureProbe()
{
  Serial.println("Setting up temperature probe...");
  tempSensor.begin();
  if(tempSensor.getDeviceCount() < 1)
  {
    Serial.println("Failed to find water probe");
    while(true);
  }
  Serial.print("Parasite power is: "); 
  if (tempSensor.isParasitePowerMode()) Serial.println("ON");
  else Serial.println("OFF");
  if(!tempSensor.getAddress(deviceAddress, 0))
  {
    Serial.print("Found ghost device but could not detect address - Check power and cabling");
    while(true);
  }
  else 
  {
    tempSensor.setResolution(deviceAddress, 12);
    Serial.print("Resolution set to ");
    Serial.print(tempSensor.getResolution(deviceAddress), DEC);
    Serial.println();
    Serial.println("Water probe setup success");
  } 
}

void Sensors::SetupECSensor()
{   
  ec.begin();
  Serial.println("EC setup success");
}

void Sensors::SetupPHSensor()
{
  ph.begin();
  Serial.println("PH setup success");
}

void Sensors::CalibratePH()
{
  float voltage, phValue, temperature = 25;
  static unsigned long timepoint = millis();
  if(millis()-timepoint>1000U){                  //time interval: 1s
      timepoint = millis();
      tempSensor.requestTemperatures();
      temperature = tempSensor.getTempC(deviceAddress);
      voltage = analogRead(PH_PIN)/1024.0*5000; // read the voltage
      phValue = ph.readPH(voltage,temperature);  // convert voltage to pH with temperature compensation
      Serial.print("temperature:");
      Serial.print(temperature,1);
      Serial.print("^C  pH:");
      Serial.println(phValue,2);
  }
  ph.calibration(voltage,temperature);
}

float Sensors::GetAverageTemp()
{
  tempSensor.requestTemperatures();
  return tempSensor.getTempC(deviceAddress);
}

float Sensors::GetAverageEC()
{
  float voltage = 0.0;
  float ecArray[10];
  for(int i=0; i<10; i++)
  {
    voltage = analogRead(EC_PIN)/1024.0*5000;
    ecArray[i] = ec.readEC(voltage, GetAverageTemp())*500.0; // x500 from ms to ppm
    delay(1000);
  }
  return GetAvgRange(ecArray, 10);
}

float Sensors::GetAveragePH()
{
  float voltage = 0.0;
  float phArray[10];
  for(int i=0; i<10; i++)
  {
    voltage = analogRead(PH_PIN)/1024.0*5000;
    phArray[i] = ph.readPH(voltage, GetAverageTemp());
    delay(1000);
  }
  return GetAvgRange(phArray, 10);
}
