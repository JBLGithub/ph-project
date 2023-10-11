#include "TempHumi.h"

TempHumi::TempHumi(int temp_humi_pin)
{
  PIN = temp_humi_pin;
}

void TempHumi::UpdateTempHumi()
{
  DHT.read11(PIN);
  TEMP = DHT.temperature;
  HUMI = DHT.humidity;
}
