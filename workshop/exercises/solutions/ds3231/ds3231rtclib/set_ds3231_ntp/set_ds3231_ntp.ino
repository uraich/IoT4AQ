/**
 * set_ds3231_ntp.ino: Gets time and date from NTP and sets the ESP32 RTC
 * The ESP32 RTC is read back and its values are transmitted to the
 * ds3231 RTC. THis version uses RTClib.
 * In order to use the battery back-up RTC we must have two programs:
 * This one, which sets the time and date on the ds3231
 * The full program, which will read time and date from the ds3231 and set
 * the internal ESP32 RTC. The internal ESP32 RTC will then be used for all 
 * time functions. 
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

void setup(){
  struct tm timeinfo;
  unsigned char seconds,minutes,hours;
  unsigned char day, month, year, dayOfWeek;
  RTC_DS3231 ds3231;
  ESP32Time esp32RTC;
  String dateString,timeString;
  
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if (ssid == "your SSID") {
    Serial.println("Please set your SSID and password and re-run the program");
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
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  
  // get the time from the ESP32 and set up the RTC
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    while (true)
      delay(100); // wait for reset
  }
  
  // check if ds3231 is connected and accessible
  if (!ds3231.begin()) {
    Serial.println("Could not find ds3231 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }  

  dateString = esp32RTC.getTime("%b %d %Y");
  timeString = esp32RTC.getTime();
  Serial.print("DS3231 time and date will be set to ");
  Serial.print(dateString.c_str());
  Serial.print(" ");
  Serial.println(timeString.c_str());
  ds3231.adjust(DateTime(dateString.c_str(),timeString.c_str()));
}

void loop(){
}
