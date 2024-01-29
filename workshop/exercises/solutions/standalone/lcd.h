/* include file for the LCD functions */

#ifndef __LCD_H__
#define __LCD_H__

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Time.h>  // time functions using the ESP32 RTC

void lcd_begin();
void lcdWriteFrame(void);
void lcdWriteTimeStamp(char *);
void lcdWriteMeas(int, int, int, int, int);
#endif
