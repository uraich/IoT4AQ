/**
 * thingSpeak_demo.ino: Connects to the WiFi network and the ThingSpeak server
 * Sends temperature, humidity and dust concentration measurements
 * to the ThingsSpeak channel
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>
#include <DHT11.h>
#include <PMS5003.h>

#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define DHT11_DATALINE 16
#define AVERAGE_OVER  5.0
#define HTTP_SUCCESS  200
WiFiClient  client;
DHT11 dht11(DHT11_DATALINE);       // create a DHT11 object
PMS5003 pms5003 = PMS5003(34,33);  // create a PMS5003 object

void setup() {
  Serial.begin(115200);  //Initialize serial
  while (!Serial); { // wait for serial port to connect.
  }
  
  WiFi.mode(WIFI_STA);
    // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, password);  // Connect to WPA/WPA2 network. 
      Serial.print(".");
      delay(5000);     
    } 
    Serial.print("\nConnected on IP ");
    Serial.println(WiFi.localIP());
  }

  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  char valTxt[10];
  pms5003Data dustMeas;
  int tmp;
  int temperature;
  int humidity;
  int pm_1_0, pm_2_5, pm_10;

  float temperature_f;
  float humidity_f;
  float pm_1_0_f, pm_2_5_f, pm_10_f;
  
  // The free version of ThingSpeak allows to send 1 measurement point every 15 s
  // We can take a measurement on the DHT11 and PMS5003 ~ every 3 s
  // Therefore we take 5 measurements, calculate the average and send this value

  temperature = 0;
  humidity    = 0;
  pm_1_0      = 0;
  pm_2_5      = 0;
  pm_10       = 0;
  
  for (int i=0; i<AVERAGE_OVER;i++) {
    // read the temperature
    tmp =  dht11.readTemperature();
    
    // check for errors
    if (tmp == DHT11::ERROR_TIMEOUT)
      Serial.println("DHT11 Timeout error when reading the temperature. Please check your cabling!");
    else if  (tmp == DHT11::ERROR_CHECKSUM)
      Serial.println("DHT11 checksum error when reading the temperature");
    else {
      // print the DHT measurement results into the result string
      // first the temperature
      snprintf(valTxt,3,"%2d",tmp);
      Serial.print("Temperature: ");
      Serial.print(valTxt);
      Serial.println("°C");
      // update the temperature sum
      temperature += tmp;
    }
    delay(1000);
    
    // then the humidity
    tmp = dht11.readHumidity();
    // check for errors
    if (tmp == DHT11::ERROR_TIMEOUT)
      Serial.println("DHT11 Timeout error when reading the humidity. Please check your cabling!");
    else if  (tmp == DHT11::ERROR_CHECKSUM)
      Serial.println("DHT11 checksum error when reading the humidity");
    else {    
      snprintf(valTxt,3,"%2d",tmp);
      Serial.print("Humidity:    ");
      Serial.print(valTxt);
      Serial.println("%");
      // update the humidity sum
      humidity += tmp;
    }
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
    pm_1_0 += dustMeas.pm1_0;
    
    // print pm2.5 to the serial line
    snprintf(valTxt,5,"%3d",dustMeas.pm2_5);
    Serial.print(", pm 2.5: ");
    Serial.print(valTxt);
    pm_2_5 += dustMeas.pm2_5;

    // print pm10 to the serial line
    snprintf(valTxt,5,"%3d",dustMeas.pm10);
    Serial.print(", pm 10: ");
    Serial.println(valTxt);
    pm_10 += dustMeas.pm10;
    // end of measurement data
    Serial.println();
    delay(1000);
  }
  temperature_f = (float)temperature / AVERAGE_OVER;
  humidity_f    = (float)humidity / AVERAGE_OVER;
  pm_1_0_f      = (float)pm_1_0 / AVERAGE_OVER;
  pm_2_5_f      = (float)pm_2_5 / AVERAGE_OVER;
  pm_10_f       = (float)pm_10 / AVERAGE_OVER;

  // calculate = average and set the fields with the values
  ThingSpeak.setField(1, temperature_f);
  ThingSpeak.setField(2, humidity_f);
  ThingSpeak.setField(3, pm_1_0_f);
  ThingSpeak.setField(4, pm_2_5_f);
  ThingSpeak.setField(5, pm_10_f);
  
  // write to the ThingSpeak channel
  int retCode = ThingSpeak.writeFields(channel_ID, API_write_key);
  if(retCode == HTTP_SUCCESS){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(retCode));
  }
  Serial.println();
  Serial.println("|--------------------------------------------------|");
  Serial.println("| Average measurements sent to ThingSpeak          |");
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
  
  // print pm10 to the serial line
  snprintf(valTxt,8,"%5.2f", pm_10_f);
  Serial.print(", pm 10: ");
  Serial.println(valTxt);
  Serial.println();
  delay(3000);
}
