#ifndef LCDSCREEN_H
#define LCDSCREEN_H

#define uint8_t byte
#include <LiquidCrystal.h>
#include <Arduino.h>

class LCDScreen
{
  public:
    int brightness;
    int led1wave;
    int led2wave;
    int led3wave;

    LCDScreen();
    bool Loop();

  private:
    LiquidCrystal lcd;
    int xcurrent;
    int ycurrent;

    void Right();
    void Up();
    void Down();
    void Left();

    void PrintBrightness();
    void PrintBlue();
    void PrintGreen();
    void PrintRed();
    void ClearCursor();
    void PrintCursor();
};

#endif
