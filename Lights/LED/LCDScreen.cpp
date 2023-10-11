#include "LCDScreen.h"

LCDScreen::LCDScreen():lcd(8,  9,  4,  5,  6,  7)
{

  //Symbols
  byte light[8] = 
  {
    0b00000,
    0b00000,
    0b01000,
    0b01000,
    0b01000,
    0b01110,
    0b00000,
    0b00000
  };

  byte lambda1[8] =
  {
    0b00011,
    0b00001,
    0b00001,
    0b10001,
    0b01001,
    0b01000,
    0b10100,
    0b10100
  };

  byte lambda2[8] =
  {
    0b00011,
    0b00001,
    0b00011,
    0b10010,
    0b01011,
    0b01000,
    0b10100,
    0b10100
  };

  byte lambda3[8] =
  {
    0b00011,
    0b00001,
    0b00011,
    0b10001,
    0b01011,
    0b01000,
    0b10100,
    0b10100
  };

  byte updown[8] = 
  {
    0b00000,
    0b00100,
    0b01010,
    0b00000,
    0b00000,
    0b01010,
    0b00100,
    0b00000
  };

  byte hyphen[8] = 
  {
    0b00000,
    0b00000,
    0b00000,
    0b01110,
    0b00000,
    0b00000,
    0b00000,
    0b00000
  };

  lcd.begin(16, 2);
  lcd.createChar(1, light);
  lcd.createChar(2, lambda1);
  lcd.createChar(3, lambda2);
  lcd.createChar(4, lambda3);
  lcd.createChar(5, updown);
  lcd.createChar(6, hyphen);

  xcurrent = 5;
  ycurrent = 0;
  brightness = 100;
  led1wave = 460;
  led2wave = 560;
  led3wave = 660;

  PrintBrightness();
  PrintBlue();
  PrintGreen();
  PrintRed();
  PrintCursor();
}

bool LCDScreen::Loop()
{
  int change = false;
  int x;
  x = analogRead(0);
  
  if (x < 60) {
    ClearCursor();
    Right();
    PrintCursor();
  }
  else if (x < 200) {
    Up();
    change = true;
  }
  else if (x < 400){
    Down();
    change = true;
  }
  else if (x < 600){
    ClearCursor();
    Left();
    PrintCursor();
  }
  
  return change; 
}

void LCDScreen::Right()
{
  if(xcurrent == 5 && ycurrent == 0)
  {
    xcurrent = 15;
  }
  else if(xcurrent == 15 && ycurrent == 0)
  {
    xcurrent = 5;
    ycurrent = 1;
  }
  else if(xcurrent == 5 && ycurrent == 1)
  {
    xcurrent = 15;
  }
  else if(xcurrent == 15 && ycurrent == 1)
  {
    xcurrent = 5;
    ycurrent = 0;
  }
}

void LCDScreen::Up()
{
  if(xcurrent == 5 && ycurrent == 0)
  {
    if(brightness < 250)
    {
      brightness = brightness + 5;
    }
    else
    {
      brightness = 255;
    }
    PrintBrightness();
  }
  else if(xcurrent == 15 && ycurrent == 0)
  {
    if(led1wave < 775)
    {
      led1wave = led1wave + 5;
    }
    else
    {
      led1wave = 780;
    }
    PrintBlue();
  }
  else if(xcurrent == 5 && ycurrent == 1)
  {
    if(led2wave < 775)
    {
      led2wave = led2wave + 5;
    }
    else
    {
      led2wave = 780;
    }
    PrintGreen();
  }
  else if(xcurrent == 15 && ycurrent == 1)
  {
    if(led3wave < 775)
    {
      led3wave = led3wave + 5;
    }
    else
    {
      led3wave = 780;
    }
    PrintRed();
  }
}

void LCDScreen::Down()
{
  if(xcurrent == 5 && ycurrent == 0)
  {
    if(brightness > 5)
    {
      brightness = brightness - 5;
    }
    else
    {
      brightness = 0;
    }
    PrintBrightness();
  }
  else if(xcurrent == 15 && ycurrent == 0)
  {
    if(led1wave > 385)
    {
      led1wave = led1wave - 5;
    }
    else
    {
      led1wave = 380;
    }
    PrintBlue();
  }
  else if(xcurrent == 5 && ycurrent == 1)
  {
    if(led2wave > 385)
    {
      led2wave = led2wave - 5;
    }
    else
    {
      led2wave = 380;
    }
    PrintGreen();
  }
  else if(xcurrent == 15 && ycurrent == 1)
  {
    if(led3wave > 385)
    {
      led3wave = led3wave - 5;
    }
    else
    {
      led3wave = 380;
    }
    PrintRed();
  }
}

void LCDScreen::Left()
{
  if(xcurrent == 5 && ycurrent == 0)
  {
    xcurrent = 15;
    ycurrent = 1;
  }
  else if(xcurrent == 15 && ycurrent == 0)
  {
    xcurrent = 5;
  }
  else if(xcurrent == 5 && ycurrent == 1)
  {
    xcurrent = 15;
    ycurrent = 0;
  }
  else if(xcurrent == 15 && ycurrent == 1)
  {
    xcurrent = 5;
  }
}

void LCDScreen::PrintBrightness()
{
 lcd.setCursor(0,0);
 lcd.write(1);
 lcd.write(6);
 if(brightness < 100) lcd.print(0); 
 lcd.print(brightness);
}

void LCDScreen::PrintBlue()
{
 lcd.setCursor(10, 0);
 lcd.write(2);
 lcd.write(6);
 if(led1wave < 100) lcd.print(0); 
 lcd.print(led1wave);
}

void LCDScreen::PrintGreen()
{
 lcd.setCursor(0, 1);
 lcd.write(3);
 lcd.write(6);
 if(led2wave < 100) lcd.print(0); 
 lcd.print(led2wave);
}

void LCDScreen::PrintRed()
{
 lcd.setCursor(10, 1);
 lcd.write(4);
 lcd.write(6);
 if(led3wave < 100) lcd.print(0); 
 lcd.print(led3wave);
}

void LCDScreen::ClearCursor()
{
 lcd.setCursor(5, 0);
 lcd.print(" ");
 lcd.setCursor(15, 0);
 lcd.print(" ");
 lcd.setCursor(5, 1);
 lcd.print(" ");
 lcd.setCursor(15, 1);
 lcd.print(" ");
}

void LCDScreen::PrintCursor()
{
 lcd.setCursor(xcurrent, ycurrent);
 lcd.write(5);
}
