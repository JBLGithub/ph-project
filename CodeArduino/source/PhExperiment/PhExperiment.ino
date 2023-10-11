#include "PhRegulator.h"
PhRegulator* regulator;

void setup() 
{
  Serial.begin(115200);
  regulator = new PhRegulator();
}

void loop() 
{
  regulator->main_loop(); 
}
