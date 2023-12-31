#include "Tools.h"


CRGB ConvertWaveToRGB(float wavelength)
{
  float Gamma = 0.80;
  float IntensityMax = 255;
  float factor, red, green, blue;
  
  if((wavelength >= 380) && (wavelength < 440))
  {
    red = -(wavelength - 440) / (440 - 380);
    green = 0.0;
    blue = 1.0;
  }
  else if((wavelength >= 440) && (wavelength < 490))
  {
    red = 0.0;
    green = (wavelength - 440) / (490 - 440);
    blue = 1.0;
  }
  else if((wavelength >= 490) && (wavelength < 510))
  {
    red = 0.0;
    green = 1.0;
    blue = -(wavelength - 510) / (510 - 490);
  }
  else if((wavelength >= 510) && (wavelength < 580))
  {
    red = (wavelength - 510) / (580 - 510);
    green = 1.0;
    blue = 0.0;
  }
  else if((wavelength >= 580) && (wavelength<645))
  {
    red = 1.0;
    green = -(wavelength - 645) / (645 - 580);
    blue = 0.0;
  }
  else if((wavelength >= 645) && (wavelength<781))
  {
    red = 1.0;
    green = 0.0;
    blue = 0.0;
  }
  else
  {
    red = 0.0;
    green = 0.0;
    blue = 0.0;
  };

  
  // Let the intensity fall off near the vision limits
  if((wavelength >= 380) && (wavelength < 420))
  {
    factor = 0.3 + 0.7*(wavelength - 380) / (420 - 380);
  }
  else if((wavelength >= 420) && (wavelength < 701))
  {
    factor = 1.0;
  }
  else if((wavelength >= 701) && (wavelength < 781))
  {
    factor = 0.3 + 0.7*(780 - wavelength) / (780 - 700);
  }
  else
  {
    factor = 0.0;
  };
     
  int fred = 0, fgreen = 0, fblue = 0;      
  if (red != 0){
      fred = (int)(IntensityMax * pow(red * factor, Gamma));
  }
  if (green != 0){
      fgreen = (int)(IntensityMax * pow(green * factor, Gamma));
  }
  if (blue != 0){
      fblue = (int)(IntensityMax * pow(blue * factor, Gamma));
  }

  //rbg
  CRGB colour = CRGB(fred, fblue, fgreen);
  return colour;  
}
