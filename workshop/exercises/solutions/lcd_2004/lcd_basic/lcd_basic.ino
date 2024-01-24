/**
 * lcd_basic.ino: Prints a welcome message to the IoT4AQ workshop
 * on the 2004_lcd display
 *
 * Copyright (c)  Uli Raich, January 2024
 * This program is part of the IoT4AQ workshop
 * held at the university Alioune Diop, Bambey, Sénégal
 * 
 * License: MIT
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD I2C address to 0x27
                                   // for a 20 chars and 4 line display

void setup()
{
  lcd.init();                      // initialize the lcd
  // switch on the backlight
  lcd.backlight();
  // clear the LCD memory
  lcd.clear();
  // set the cursor, the first parameter is the x position of the first character
  // to be written, the second one is the row number
  lcd.setCursor(3,0);
  // ... and print the message
  lcd.print("Welcome to the");
  lcd.setCursor(0,1);
  lcd.print("IoT4AQ workshop 2024");
   lcd.setCursor(4,2);
  lcd.print("Alioune Diop");
  lcd.setCursor(1,3);
  lcd.print("University, Bambey");
}


void loop()
{
  // loops forever without doing anything
}
