/**
 * standalone.ino: reads the time stamp from the ESP32 RTC
 * the reads temperature, hunidity and dust concentration measurements
 * and write this information to the LCD and the SD card
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <DHT11.h>
#include <PMS5003.h>
#include "setESP32RTC.h"
#include "lcd.h"
#include "sd_card.h"

#define DHT11_DATALINE 16
#define AVERAGE_OVER  5.0

DHT11 dht11(DHT11_DATALINE);       // create a DHT11 object
PMS5003 pms5003 = PMS5003(34,33);  // create a PMS5003 object
ESP32Time esp32RTC;

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial); { // wait for serial port to connect.
  }
  // set the ESP32 RTC
  setESP32RTC();
  // write the frame to the LCD
  lcdWriteFrame();
}

void loop() {
  char valTxt[10];
  pms5003Data dustMeas;
  int tmp;
  int temperature,temperature_sum;
  int humidity,humidity_sum;
  int pm_1_0_sum, pm_2_5_sum, pm_10_sum;

  float temperature_f;
  float humidity_f;
  float pm_1_0_f, pm_2_5_f, pm_10_f;

  String now;
  
  // The free version of ThingSpeak allows to send 1 measurement point every 15 s
  // We can take a measurement on the DHT11 and PMS5003 ~ every 3 s
  // Therefore we take 5 measurements, calculate the average and send this value

  temperature_sum = 0;
  humidity_sum    = 0;
 
  pm_1_0_sum  = 0;
  pm_2_5_sum  = 0;
  pm_10_sum   = 0;
  
  for (int i=0; i<AVERAGE_OVER;i++) {
    // read the temperature
    temperature =  dht11.readTemperature();
    temperature_sum += temperature;
    delay(1000);
    
    // print the DHT measurement results into the result string
    // first the temperature
    snprintf(valTxt,3,"%2d",temperature);
    Serial.print("Temperature: ");
    Serial.print(valTxt);
    Serial.println("°C");
    
    // then the humidity
    humidity = dht11.readHumidity();
    humidity_sum += humidity;
    snprintf(valTxt,3,"%2d",humidity);
    Serial.print("Humidity:    ");
    Serial.print(valTxt);
    Serial.println("%");
    //delay(1000);
    
    // finally read the dust sensor
    dustMeas = pms5003.readMeas();
    if (dustMeas.header[0] == '\0') {
      Serial.println("Checksum error");
      // give it another try
      dustMeas = pms5003.readMeas();
      if (dustMeas.header[0] == '\0') {
	      Serial.println("Two consecutive serial read errors");
	      break;
      }
    }
    // print pm1.0 to the serial line
    
    snprintf(valTxt,5,"%3d",dustMeas.pm1_0);
    Serial.print("pm 1.0: ");
    Serial.print(valTxt);
    pm_1_0_sum += dustMeas.pm1_0;
    
    // print pm2.5 to the serial line
    snprintf(valTxt,5,"%3d",dustMeas.pm2_5);
    Serial.print(", pm 2.5: ");
    Serial.print(valTxt);
    pm_2_5_sum += dustMeas.pm2_5;

    // print pm10 to the serial line
    snprintf(valTxt,5,"%3d",dustMeas.pm10);
    Serial.print(", pm 10: ");
    Serial.println(valTxt);
    // end of measurement data
    Serial.println();
    pm_10_sum += dustMeas.pm10;
    delay(1000);

    // get the time stamp and write it to the LCD
    Serial.println(esp32RTC.getTime("%H:%M:%S %d %b %Y"));
    lcdWriteTimeStamp((char *)esp32RTC.getTime("%H:%M:%S %d %b %Y").c_str());
    // write the measurements to the LCD
    lcdWriteMeas(temperature, humidity,
		 dustMeas.pm1_0, dustMeas.pm2_5, dustMeas.pm10);
  }
  
  // calculate = average and set the fields with the values
  temperature_f = (float)temperature_sum / AVERAGE_OVER;
  humidity_f    = (float)humidity_sum / AVERAGE_OVER;
  pm_1_0_f      = (float)pm_1_0_sum / AVERAGE_OVER;
  pm_2_5_f      = (float)pm_2_5_sum / AVERAGE_OVER;
  pm_10_f       = (float)pm_10_sum / AVERAGE_OVER;

  Serial.println();
  Serial.println("|--------------------------------------------------|");
  Serial.println("| Average measurements                             |");
  Serial.println("|--------------------------------------------------|");
  
  // print the average values to the serial line
  // print temperature 
  snprintf(valTxt,5,"%4.2f",temperature_f);
  Serial.print("Temperature: ");
  Serial.print(valTxt);
  Serial.println("°C");
  
  // print humidity
  snprintf(valTxt,3,"%4.2f",humidity_f);
  Serial.print("Humidity:    ");
  Serial.print(valTxt);
  Serial.println("%");

  snprintf(valTxt,8,"%5.2f", pm_1_0_f);
  Serial.print("pm 1.0: ");
  Serial.print(valTxt);
  
  // print pm2.5 to the serial line
  snprintf(valTxt,8,"%5.2f", pm_2_5_f);
  Serial.print(", pm 2.5: ");
  Serial.print(valTxt);
  
  snprintf(valTxt,8,"%5.2f", pm_10_f);
  Serial.print(", pm 10: ");
  Serial.println(valTxt);
  Serial.println();
  // write the data to the SD card
  sdWriteMeas((char *)esp32RTC.getTime("%H:%M:%S %d %b %Y").c_str(),
              temperature_f,humidity_f, pm_1_0_f, pm_2_5_f, pm_10_f);
  
  delay(3000);
}
