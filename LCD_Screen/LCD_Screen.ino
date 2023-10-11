#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
LiquidCrystal lcd(pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

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

int xcurrent = 5;
int ycurrent = 0;

int brightness = 100;
int blue = 460;
int green = 560;
int red = 660;

void setup() 
{
 //setup
 Serial.begin(9600);
 lcd.begin(16, 2);
 lcd.createChar(1, light);
 lcd.createChar(2, lambda1);
 lcd.createChar(3, lambda2);
 lcd.createChar(4, lambda3);
 lcd.createChar(5, updown);
 lcd.createChar(6, hyphen);
 
 printBrightness();
 printBlue();
 printGreen();
 printRed();
 printCursor();
 
}


void loop() 
{
  
 int x;
 x = analogRead(0);

 if (x < 60) {
   clearCursor();
   right();
   printCursor();
 }
 else if (x < 200) {
   up();
 }
 else if (x < 400){
   down();
 }
 else if (x < 600){
   clearCursor();
   left();
   printCursor();
 }
 else if (x < 800){
   selected();
 }

 delay(200);
 
}

void right()
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

void up()
{
  
}

void down()
{
  
}

void left()
{
  
}

void selected()
{
  
}

void printBrightness()
{
 lcd.setCursor(0,0);
 lcd.write(1);
 lcd.write(6);
 lcd.print(brightness);
}

void printBlue()
{
  lcd.setCursor(10, 0);
 lcd.write(2);
 lcd.write(6);
 lcd.print(blue);
}

void printGreen()
{
 lcd.setCursor(0, 1);
 lcd.write(3);
 lcd.write(6);
 lcd.print(green);
}

void printRed()
{
 lcd.setCursor(10, 1);
 lcd.write(4);
 lcd.write(6);
 lcd.print(red);
}

void clearCursor()
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

void printCursor()
{
 lcd.setCursor(xcurrent, ycurrent);
 lcd.write(5);
}
