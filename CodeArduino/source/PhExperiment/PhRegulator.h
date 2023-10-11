#ifndef PHREGULATOR_H
#define PHREGULATOR_H

//In Libraries
#include "Tools.h"
#include "Sensors.h"
#include "Relays.h"

//Out Libraries
#include <Arduino.h>


//Class
class PhRegulator {

  private:
    int InPin;
    Relay relay;
    Sensors sensors;

    float CURRENT_TEMP;
    float CURRENT_PH;
    float CURRENT_EC;

    float VOLUMEL;
    float DESIRED_PH;
    float CURRENT_ESTIMATED_PH;

    unsigned long timepoint1;
    unsigned long timepoint2;
    
  public:
    PhRegulator();
    float ReadCurrent();
    void CheckWaterSolution(int loopcount);
    float CalculatePHChange();
    void main_loop();

    

    
};

#endif
