#ifndef TEMPHUMI_H
#define TEMPHUMI_H

#include <Arduino.h>
#include <dht.h>

class TempHumi
{
  public:
    float TEMP;
    float HUMI;

    TempHumi(int temp_humi_pin);
    void UpdateTempHumi();


  private:
    dht DHT;
    int PIN;
};

#endif
