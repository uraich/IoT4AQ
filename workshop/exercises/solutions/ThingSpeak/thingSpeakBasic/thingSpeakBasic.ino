/**
 * thingSpeakBasic.ino: Connects to the WiFi network and the ThingSpeak server
 * Sends a triangular signal the temperature filed of the ThingsSpeak channel
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>
#include "secrets.h"
#include "ThingSpeak.h" // always include thingspeak header file after other header files and custom macros

#define HTTP_SUCCESS  200
WiFiClient  client;

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
  int httpResponse;
  // ramp up
  for (int temperature=20; temperature < 41; temperature++) {
    Serial.print("Sending a temperature value of ");
    Serial.println(temperature);
    httpResponse = ThingSpeak.writeField(channel_ID, 1, temperature, API_write_key);
    if(httpResponse == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(httpResponse));
    }
    delay(15000); // wait 15s, which is the max update speed a free ThingSpeak account allows
  }
  
  // ramp down
  for (int temperature=40; temperature >19; temperature--) {
    Serial.print("Sending a temperature value of ");
    Serial.println(temperature);
    
    httpResponse = ThingSpeak.writeField(channel_ID, 1, temperature, API_write_key);
    if(httpResponse == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(httpResponse));
    }
    delay(15000);
  }  
}
