#define FASTLED_INTERNAL
#include "Lighting.h"

#include <FastLED.h>

#define LedPin 9
#define NumStrip 3
CRGB leds[NumStrip];

void setupLed()
{
  FastLED.addLeds<WS2811, LedPin, RGB>(leds, NumStrip);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  FastLED.clear();
  FastLED.show();
}

void tempLed()
{
  //int* rgb = waveToRGB(450);
  leds[0]  = CRGB(255, 0, 0);
  leds[1]  = CRGB(0, 255, 0);
  leds[2]  = CRGB(0, 0, 255);
  FastLED.show();
  delay(60000);
}

/*
int* waveToRGB(double wavelength)
{
  double factor;
  double Red, Green, Blue;
  double Gamma = 0.80;
  double IntensityMax = 255;

  if((wavelength >= 380) && (wavelength < 440)) {
      Red = -(wavelength - 440) / (440 - 380);
      Green = 0.0;
      Blue = 1.0;
  } else if((wavelength >= 440) && (wavelength < 490)) {
      Red = 0.0;
      Green = (wavelength - 440) / (490 - 440);
      Blue = 1.0;
  } else if((wavelength >= 490) && (wavelength < 510)) {
      Red = 0.0;
      Green = 1.0;
      Blue = -(wavelength - 510) / (510 - 490);
  } else if((wavelength >= 510) && (wavelength < 580)) {
      Red = (wavelength - 510) / (580 - 510);
      Green = 1.0;
      Blue = 0.0;
  } else if((wavelength >= 580) && (wavelength < 645)) {
      Red = 1.0;
      Green = -(wavelength - 645) / (645 - 580);
      Blue = 0.0;
  } else if((wavelength >= 645) && (wavelength < 781)) {
      Red = 1.0;
      Green = 0.0;
      Blue = 0.0;
  } else {
      Red = 0.0;
      Green = 0.0;
      Blue = 0.0;
  }

  // Let the intensity fall off near the vision limits
  if((wavelength >= 380) && (wavelength < 420)) {
      factor = 0.3 + 0.7 * (wavelength - 380) / (420 - 380);
  } else if((wavelength >= 420) && (wavelength < 701)) {
      factor = 1.0;
  } else if((wavelength >= 701) && (wavelength < 781)) {
      factor = 0.3 + 0.7 * (780 - wavelength) / (780 - 700);
  } else {
      factor = 0.0;
  }


  int rgb[3];
  // Don't want 0^x = 1 for x <> 0
  rgb[0] = Red == 0.0 ? 0 : (int)(IntensityMax * pow(Red * factor, Gamma));
  rgb[1] = Green == 0.0 ? 0 : (int)(IntensityMax * pow(Green * factor, Gamma));
  rgb[2] = Blue == 0.0 ? 0 : (int)(IntensityMax * pow(Blue * factor, Gamma));

  return rgb;
}*/
