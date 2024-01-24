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
/* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   I use Rx=34 and Tx=33 because otherwise the PMS5003 conflicts with the DHT11 onn my system
   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
PMS5003 pms5003 = PMS5003(34,33);  // create a PMS5003 object

// define the pixel layout of the degree character
uint8_t deg[8]={0x2,0x5,0x2,0x0,0x0,0x0,0x0};

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

   // create the degree character  
  lcd.createChar(0, deg);
  
  // set the cursor, the first parameter is the x position of the first character
  // to be written, the second one is the row number
  lcd.setCursor(0,0);
  // ... and print the message
  lcd.print("Temperature:   ");
  lcd.write(0); // this prints the degree character
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity:      %");
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
  delay(1000); // we have to wait for 1s in between measurements
  humidity    = dht11.readHumidity();

  // print the DHT measurement results into the result string
  // first the temperature
  snprintf(valTxt,3,"%2d",temperature);
  Serial.print("Temperature: ");
  Serial.print(valTxt);
  Serial.println("°C");
  lcd.setCursor(13,0);
  lcd.print(valTxt);
  
  // then the humidity
  snprintf(valTxt,3,"%2d",humidity);
  lcd.setCursor(13,1);
  lcd.print(valTxt);
  Serial.print("Humidity:    ");
  Serial.print(valTxt);
  Serial.println("%");

  // read the PMS5003
  dustMeas = pms5003.readMeas();
  // print pm1.0 to the display
  snprintf(valTxt,5,"%3d",dustMeas.pm1_0);
  Serial.print("pm 1.0: ");
  Serial.print(valTxt);
  lcd.setCursor(6,2);

  lcd.print(valTxt);

  // print pm2.5 to the display
  snprintf(valTxt,5,"%3d",dustMeas.pm2_5);
  Serial.print(", pm 2.5: ");
  Serial.print(valTxt);
  lcd.setCursor(16,2);
  lcd.print(valTxt);

 // print pm10 to the display
  snprintf(valTxt,5,"%3d",dustMeas.pm10);
  Serial.print(", pm 10: ");
  Serial.println(valTxt);
  lcd.setCursor(6,3);
  lcd.print(valTxt);
 
  Serial.println();
  delay(1000);
}
