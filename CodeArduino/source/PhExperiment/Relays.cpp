#include "Relays.h"
#include <Arduino.h>

Relay::Relay(int sensorpin, int ecrelaypin, int phrelaypin, int elecpin, int eleccurrentpin, int mixerpin)
{
  Serial.begin(9600);
  Serial.println("Relays set up started...");

  sensor_on = false;
  ecphrelaymode = true;
  electrodes_on = false;
  elecacidemode = true;
  mixer_on = false;

  SensorsPin = sensorpin;
  ECRelayPin = ecrelaypin;
  PHRelayPin = phrelaypin;
  ElectrodePin = elecpin;
  ElecCurrentDirectionPin = eleccurrentpin;
  MixerPin = mixerpin;

  pinMode(SensorsPin, OUTPUT);
  pinMode(ECRelayPin, OUTPUT);
  pinMode(PHRelayPin, OUTPUT);
  pinMode(ElectrodePin, OUTPUT);
  pinMode(ElecCurrentDirectionPin, OUTPUT);
  pinMode(MixerPin, OUTPUT);
  digitalWrite(SensorsPin, HIGH); //stop
  digitalWrite(ECRelayPin, HIGH); //stop
  digitalWrite(PHRelayPin, HIGH); //stop
  digitalWrite(ElectrodePin, HIGH); //stop
  digitalWrite(ElecCurrentDirectionPin, HIGH); //stop
  digitalWrite(MixerPin, HIGH); //stop
  Serial.println("Relays set up completed.");
}

void Relay::toggleSensor()
{
  if(sensor_on){
    digitalWrite(SensorsPin, HIGH); //stop
    digitalWrite(ECRelayPin, HIGH); //stop
    digitalWrite(PHRelayPin, HIGH); //stop
    delay(100);
    Serial.println("Sensors Off");
  } else {
    digitalWrite(SensorsPin, LOW); //start
    digitalWrite(ECRelayPin, LOW); //start
    digitalWrite(PHRelayPin, HIGH); //stop
    ecphrelaymode = true;
    delay(100);
    Serial.println("Sensors On");
  }
  sensor_on = !sensor_on;
}

void Relay::toggleECPHRelay()
{
  if(sensor_on)
  {   
    digitalWrite(SensorsPin, HIGH); //stop
    delay(100);
    if(ecphrelaymode)
    {
      digitalWrite(ECRelayPin, HIGH); //stop
      digitalWrite(PHRelayPin, LOW); //start
      Serial.println("switch ec to ph");
    } else 
    {
      digitalWrite(PHRelayPin, HIGH); //stop
      digitalWrite(ECRelayPin, LOW); //start
      Serial.println("switch ph to ec");
    }
    delay(100);
    digitalWrite(SensorsPin, LOW); //start
    delay(200);
    ecphrelaymode = !ecphrelaymode;
  }
  else
  {
    Serial.println("Cannot use without sensor on");
  }
}

void Relay::toggleElectrode()
{
  if(electrodes_on){
    digitalWrite(ElectrodePin, HIGH); //stop
    Serial.println("Electrode Off");
  } else {
    digitalWrite(ElectrodePin, LOW); //start
    Serial.println("Electrode On");
  }
  electrodes_on = !electrodes_on;
}

void Relay::toggleAcidMode()
{
  toggleElectrode(); //turn off electrode first to avoid short cut
  delay(100);
  if(!elecacidemode){
    digitalWrite(ElecCurrentDirectionPin, HIGH); //switch
    Serial.println("Acid Mode");
  } else {
    digitalWrite(ElecCurrentDirectionPin, LOW); //switch
    Serial.println("Basic Mode");
  }
  elecacidemode = !elecacidemode;
  delay(100);
  toggleElectrode();
}

void Relay::toggleMixer()
{
  if(mixer_on){
    digitalWrite(MixerPin, HIGH); //stop
    Serial.println("Mixer Off");
  } else {
    digitalWrite(MixerPin, LOW); //start
    Serial.println("Mixer On");
  }
  mixer_on = !mixer_on;
}
