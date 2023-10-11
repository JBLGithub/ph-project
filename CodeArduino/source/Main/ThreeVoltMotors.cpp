#include "ThreeVoltMotors.h"

#define MixerPositivePin 10
#define MixerNegativePin 11

bool on_mixer = false;

void setupMotor()
{
  pinMode(MixerPositivePin, OUTPUT);
  digitalWrite(MixerPositivePin, HIGH); //stop
  pinMode(MixerNegativePin, OUTPUT);
  digitalWrite(MixerNegativePin, HIGH); //stop
}

void toggleMixers()
{
  if(on_mixer)
  {
    digitalWrite(MixerPositivePin, HIGH); //stop
    digitalWrite(MixerNegativePin, HIGH); //stop
  }
  else
  {
    digitalWrite(MixerPositivePin, LOW); //start
    digitalWrite(MixerNegativePin, LOW); //start
  }
  on_mixer = !on_mixer;
}
