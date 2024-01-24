/**
 * lcd_meas.ino: reads temperature and humidity from the DHT11
 * and the dust concentration from the PMS5003
 * prints the measured results for 
 * temperature, humidity, pm1.0, pm2.5 and pm10 
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
// include the libraries needed to do the measurements
#include <DHT11.h>
#include <PMS5003.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD I2C address to 0x27
                                   // for a 20 chars and 4 line display

#define DHT11_DATALINE 16

DHT11 dht11(DHT11_DATALINE);       // create a DHT11 object
PMS5003 pms5003 = PMS5003();       // create a PMS5003 object

void setup()
{
  Serial.begin(115200);
    if (!Serial)
      delay(10);
  lcd.init();                      // initialize the lcd
  // switch on the backlight
  lcd.backlight();
  // clear the LCD memory
  lcd.clear();
  // set the cursor, the first parameter is the x position of the first character
  // to be written, the second one is the row number
  lcd.setCursor(0,0);
  // ... and print the message
  lcd.print("Measurement results:");
  lcd.setCursor(0,1);
  lcd.print("Temp:    C Humi:   %");
  lcd.setCursor(0,2);
  lcd.print("pm1.0:    pm2.5:    ");
  lcd.setCursor(0,3);
  lcd.print("pm10:   ");
}


void loop()
{
  char valTxt[5];
  pms5003Data dustMeas;
  int temperature;
  int humidity;
  
  // read the temperature
  temperature = dht11.readTemperature();
  // reading the dust measurement will take ~ 1s
  // dustMeas = pms5003.readMeas();
  // read the humidity
  humidity    = dht11.readHumidity();
  // print the DHT measurement results into the result string
  snprintf(valTxt,3,"%2d",temperature);
  Serial.print("Temperature: ");
  Serial.print(valTxt);
  Serial.println("°C");
  lcd.setCursor(6,1);
  lcd.print(valTxt);
  /*
  lcd.setCursor(0,2);
  snprintf(line,20,"pm1.0:  %04d, pm2.5: %02d",dustMeas.pm1_0,dustMeas.pm2_5);  
  lcd.print(line);
  lcd.setCursor(1,3);
  snprintf(line,20,"pm10:  %04d",dustMeas.pm10);  
  lcd.print(line);
  */
  delay(1000);
}
