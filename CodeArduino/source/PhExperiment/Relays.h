#ifndef RELAYS_H
#define RELAYS_H

//Out Libraries
#include <Arduino.h>

//CLass
class Relay
{ 
  private:
    int SensorsPin;
    int ECRelayPin;
    int PHRelayPin;
    int ElectrodePin;
    int ElecCurrentDirectionPin;
    int MixerPin;
    
    bool sensor_on;
    bool ecphrelaymode;
    bool electrodes_on;
    bool mixer_on;

  
  public:
    bool elecacidemode;
  
    Relay(int sensorpin, int ecrelaypin, int phrelaypin, int elecpin, int eleccurrentpin, int mixerpin);
    void toggleSensor();
    void toggleECPHRelay();
    void toggleMixer();
    void toggleElectrode();
    void toggleAcidMode();
};

#endif
