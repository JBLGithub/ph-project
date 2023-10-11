#include "PhRegulator.h"
#include "Tools.h"

PhRegulator::PhRegulator() : relay(13, 12, 11, 10, 9, 8), sensors(4, 5, 3)
{
  Serial.println("Setup begin.....");
  VOLUMEL = 2.0;
  DESIRED_PH = -1.0;
  CURRENT_ESTIMATED_PH = -1.0;
  InPin = A3;
  pinMode(InPin, INPUT);
  
  //Setup
  relay.toggleSensor();
  sensors.SetupTemperatureProbe();
  sensors.SetupECSensor();
  relay.toggleECPHRelay();
  sensors.SetupPHSensor();
  relay.toggleECPHRelay();

  Serial.println("Setup successful!");
  Serial.println("PH Regulator starting...");
  CheckWaterSolution(1);
  CheckWaterSolution(5);
  relay.toggleSensor();
  timepoint1 = millis();
  timepoint2 = millis();
  
}

void PhRegulator::main_loop()
{

  if(DESIRED_PH < 0)
  {

    Serial.println("Enter the desired PH: ");
    while(Serial.available() == 0);

    float desiredFloat = Serial.readString().toFloat();
    if(desiredFloat < 2.0 || desiredFloat > 10)
    {
      Serial.println("Invalid pH value (between 2.0 and 10.0)");
      return;
    }

    DESIRED_PH = desiredFloat;
    CURRENT_ESTIMATED_PH = CURRENT_PH;

    relay.toggleElectrode();
    if(DESIRED_PH > CURRENT_ESTIMATED_PH)
    {
      relay.toggleAcidMode();
    }

    timepoint1 = millis();
    timepoint2 = millis();
    
  }
  else 
  {

    if(millis()-timepoint1 > 10L*1000L) // 10s 
    {
      timepoint1 = millis();
      float phChange = CalculatePHChange();

      CURRENT_ESTIMATED_PH = CURRENT_ESTIMATED_PH + phChange;
      Serial.print("Current Estimated PH: ");
      Serial.println(CURRENT_ESTIMATED_PH);
      Serial.print("PH Change: ");
      Serial.println(phChange);
    }

    if(millis()-timepoint2 > 5L*60L*1000L) // 5m
    {
      relay.toggleElectrode();
      relay.toggleMixer();
      delay(60000);
      relay.toggleMixer();
      relay.toggleSensor();
      CheckWaterSolution(5);
      relay.toggleSensor();
      relay.toggleElectrode();

      timepoint1 = millis();
      timepoint2 = millis();
    }
    
  }
  
}


float PhRegulator::CalculatePHChange()
{
  float avgCurrent = ReadCurrent();

  Serial.print("Average current: ");
  Serial.println(avgCurrent);
  
  float timesecond = 10;
  float power = pow(10, (CURRENT_ESTIMATED_PH-5));
  
  float top = avgCurrent * timesecond * 6.241 * power;
  float bottom = VOLUMEL * 6.02214076;

  float phChange = 0.0;
  if(relay.elecacidemode)
  {
    phChange = -log(1+(top/bottom));
  }
  else
  {
    phChange = -log(1-(top/bottom));
  }

  /*
  Serial.println("------");
  Serial.println(avgCurrent);
  Serial.println(timesecond);
  Serial.println(power);
  Serial.println(top);
  Serial.println(bottom);
  Serial.println(phChange);
  Serial.println("------");*/
  
  return phChange;
}

void PhRegulator::CheckWaterSolution(int loopcount)
{
  
  float tp = 0.0;
  float ec = 0.0;
  float ph = 0.0;
  for(int i=0; i<loopcount; i++)
  {
    tp += sensors.GetAverageTemp();
    ec += sensors.GetAverageEC();
    relay.toggleECPHRelay();
    ph += sensors.GetAveragePH();
    relay.toggleECPHRelay();
  }

  CURRENT_TEMP = RoundResult(tp/float(loopcount));
  CURRENT_EC = RoundResult(ec/float(loopcount));
  CURRENT_PH = RoundResult(ph/float(loopcount));

  Serial.print("Temperature: ");
  Serial.print(CURRENT_TEMP);
  Serial.print("ºC\tEC: ");
  Serial.print(CURRENT_EC);
  Serial.print("ppm\tPH: ");
  Serial.println(CURRENT_PH);
  
}


float PhRegulator::ReadCurrent()
{

  float arrCur[200];
  for(int i=0; i<200; i++)
  {
    arrCur[i] = analogRead(InPin);
    delay(3);
  }
  
  float averageSensorValue = GetAvgRange(arrCur, 200);
  Serial.print("avg CurrentSensor value: ");
  Serial.println(averageSensorValue);
  float sensitivity = 0.066;
  float voltage = ((averageSensorValue * (5.0 / 1024.0)) - 2.5)/sensitivity;
  float amperage = RoundResult(voltage);

  if(amperage < 0.0)  return 0.0;
  return amperage;
}
