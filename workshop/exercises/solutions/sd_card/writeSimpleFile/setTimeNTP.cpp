/**
 * setTimeNTP.cpp: During the workshop we do not have a battery on the RTC 
 * and date and time must be read from NTP after each reset.
 * The function in this file is essentially the same code as set_ds1307_ntp.ino,  
 * here however implemented as a function. A simple function call will then
 * pick up date and time from NTP and set both, the ESP32RTC and the ds1307
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>
#include <RTClib.h>
#include <ESP32Time.h>

const char* ssid     = "your SSID";
const char* password = "your password";

const char* ntpServer = "pool.ntp.org";

// it is better to use UTC because this will avoid discontinuities in time
// due to daylight saving
// In any case you can easily convert UTC to local time offline

const long  gmtOffset_sec = 0;        // use UTC
const int   daylightOffset_sec = 0;

void setTimeNTP(void) {
  struct tm timeinfo;
  unsigned char seconds,minutes,hours;
  unsigned char day, month, year, dayOfWeek;
  RTC_DS1307 ds1307;
  ESP32Time esp32RTC;
  String dateString,timeString;

  // check if WiFi is already connect and connect to it if not
  if (!(WiFi.status() == WL_CONNECTED)) {
      if (ssid == "your SSID") {
        Serial.println("Please setup your correct SSID first");
        return;
      }
      // Connect to Wi-Fi
      Serial.print("Connecting to ");
      Serial.println(ssid);
      WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected.");
    }
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // get the time from the ESP32 and set up the RTC
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    while (true)
      delay(100); // wait for reset
  }
  
  // check if ds1307 is connected and accessible
  if (!ds1307.begin()) {
    Serial.println("Could not find ds1307 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }  

  dateString = esp32RTC.getTime("%b %d %Y");
  timeString = esp32RTC.getTime();
  Serial.print("DS1307 time and date will be set to ");
  Serial.print(dateString.c_str());
  Serial.print(" ");
  Serial.println(timeString.c_str());
  ds1307.adjust(DateTime(dateString.c_str(),timeString.c_str()));
}
