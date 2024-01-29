/* lcd.cpp: Functions to write the LCD
 * void frame(): a function to write the frame text
 * void insertMeas(float temp, float humi, float pm1_0, float pm2.5, float pm10)
 * Copyright U. Raich, Jan. 2024
 * This program is part of the IoT4AQ workshop held at the
 * Alioune Diop University, Bambey, Sénégal
 * It is released under the MIT license
 */

#include <Arduino.h>
#include "lcd.h"

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD I2C address to 0x27
                                   // for a 20 chars and 4 line display
uint8_t deg[8]={0x2,0x5,0x2,0x0,0x0,0x0,0x0};

void lcd_begin() {
  lcd.init();                      // initialize the lcd
  // switch on the backlight
  lcd.backlight();
  // clear the LCD memory
  lcd.clear();
  // create the degree character  
  lcd.createChar(0, deg);
}

void lcdWriteFrame(void) {
  // writes the framework to the LCD screen
  // set the cursor, the first parameter is the x position of the first character
  // to be written, the second one is the row number
  lcd_begin();
  lcd.setCursor(0,1);
  // ... and print the message
  lcd.print("Temp:   ");
  lcd.write(0); // this prints the degree character
  lcd.print("C");
  lcd.setCursor(11,1);
  lcd.print("Humi:   %");
  lcd.setCursor(0,2);
  lcd.print("pm1.0:    pm2.5:    ");
  lcd.setCursor(0,3);
  lcd.print("pm10:   ");
}

void lcdWriteTimeStamp(char * timeStamp) {
  // start at first character of first line
  lcd.setCursor(0,0);
  lcd.print(timeStamp);
  
}

void lcdWriteMeas(int temperature, int humidity,
		  int pm_1_0, int pm_2_5, int pm_10) {
  char valTxt[10];
  // write the temperature
  snprintf(valTxt,3,"%2d",temperature);
  lcd.setCursor(6,1);
  lcd.print(valTxt);

  // write the humidity
  snprintf(valTxt,3,"%2d",humidity);
  lcd.setCursor(17,1);
  lcd.print(valTxt);
  
  // write pm 1.0
  snprintf(valTxt,4,"%3d",pm_1_0);
  lcd.setCursor(6,2);
  lcd.print(valTxt);
  
  // write pm2.5
  snprintf(valTxt,4,"%3d",pm_2_5);
  lcd.setCursor(16,2);
  lcd.print(valTxt);

  // write pm10
  snprintf(valTxt,4,"%3d",pm_10);
  lcd.setCursor(6,3);
  lcd.print(valTxt);

}
