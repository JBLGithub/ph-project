#include "WebServer.h"
#include "HydroTime.h"
#include "waterTempSensor.h"
#include "phsensor.h"
#include "ecsensor.h"
#include "ThreeVoltMotors.h"
#include "Lighting.h"
#include <EEPROM.h>

#define KVALUEADDR 0x00
unsigned long my_clock;
unsigned int hydro_counter;

void setup() {

  //clean memory
  for(byte i = 0;i< 8; i++   )
  {
    EEPROM.write(KVALUEADDR+i, 0xFF);
  }
  analogReference(INTERNAL4V3);
  Serial.begin(9600);
  //while (!Serial) ;
  //setupWebServer();
  //setupTime();
  setupWaterTemp();
  setupPH();
  //setupEC();
  //setupMotor();
  //my_clock = millis();
  //hydro_counter = 1;
}

void loop() {

  calibratePH();


  /*
  checkClient();
  if((millis() - my_clock) > 10L*1000L)
  {
    if(hydro_counter == 5 || hydro_counter == 6)
    {
      toggleMixers();
      Serial.println("Toggle Mixers");
      if(hydro_counter == 5)
      {
        hydro_counter++;
      }
      else
      {
        hydro_counter = 1;
      }
    }
    else 
    {
      updateValues();
      hydro_counter++;
    }
    my_clock = millis();
  }*/
}
