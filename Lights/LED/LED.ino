#define FASTLED_INTERNAL
#include <FastLED.h>
#include "Tools.h"
#include "LCDScreen.h"
#include "TempHumi.h"

#define LED_PIN 13  
#define NUM_LED 24
LCDScreen screen;
CRGB LEDs[NUM_LED];
TempHumi th(A2);

void setup()
{
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LED_PIN, GRB>(LEDs, NUM_LED);
  setColourToLEDs();
}

void loop()
{
  bool change = screen.Loop();
  if(change)
  {
    setColourToLEDs();
  }

  th.UpdateTempHumi();
  Serial.println(th.TEMP);
  Serial.println(th.HUMI);
  
  delay(200);
}

void setColourToLEDs()
{

  CRGB blue = ConvertWaveToRGB(screen.led1wave);
  CRGB green = ConvertWaveToRGB(screen.led2wave);
  CRGB red = ConvertWaveToRGB(screen.led3wave);
  
  for(int i=0; i<NUM_LED; i++)
  {
    if(i % 3 == 0)
    {
      LEDs[i] = blue;
    }
    else if(i % 3 == 1)
    {
      LEDs[i] = red;
    }
    else if(i % 3 == 2)
    {
      LEDs[i] = green;
    }
  }

  FastLED.setBrightness(screen.brightness);
  FastLED.show();
  
}
