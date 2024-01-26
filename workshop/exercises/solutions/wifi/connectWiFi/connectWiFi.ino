/**
 * scanWiFi.ino: Connects to the WiFi network and prints its IP address
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>

const char* ssid     = "your SSID";
const char* password = "your password";

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // put WiFi to station mode
  WiFi.mode(WIFI_STA);
  if (strcmp(ssid, "your SSID") == 0) { // check if the user put his correct SSID
    Serial.println("Please modify the program and insert your correct SSID");
    while (true)
      delay(100); // wait until reboot
  }
    
  WiFi.begin(ssid,password); // connect to the network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected on ");
  Serial.println(WiFi.localIP());
}

void loop() {

}
