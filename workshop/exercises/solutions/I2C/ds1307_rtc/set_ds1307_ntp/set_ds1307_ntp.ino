/**
 * set_ds1307_ntp.ino: Gets time and date from NTP and sets the ESP32 RTC
 * The ESP32 RTC is read back and its values are transmitted to the
 * ds1307 RTC. 
 * In order to use the battery back-up RTC we must have two programs:
 * This one, which sets the time and date on the ds1307
 * The full program, which will read time and date from the ds1307 and set
 * the internal ESP32 RTC. The internal ESP32 RTC will then be used for all 
 * time functions. 
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>
#include <Wire.h>
#include "time.h"

const char* ssid     = "your SSID";
const char* password = "your WiFi password";

const char* ntpServer = "pool.ntp.org";

// it is better to use UTC because this will avoid discontinuities in time
// due to daylight saving
// In any case you can easily convert UTC to local time offline

const long  gmtOffset_sec = 0;        // use UTC
const int   daylightOffset_sec = 0;

// constants needed to access the DS1307 RTC
#define DS1307_ADDRESS 0x68
#define DS1307_TIME    0x00

// The DS1307 uses bcd (binary coded decimal) encoding
// We must therefore convert the binary time values for seconds, minutes ...
// to bcd before sending them to the DS1307

unsigned char bin2bcd(unsigned char int_bin) {
  unsigned char high_nibble = int_bin / 10;
  unsigned char low_nibble  = int_bin % 10;
  return (high_nibble << 4) | low_nibble;
}

void setup(){
  struct tm timeinfo;
  unsigned char seconds,minutes,hours;
  unsigned char day, month, year, dayOfWeek;
  byte err;

  Serial.begin(115200);
  while (!Serial)
    delay(10);

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
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    while (true)
      delay(100); // wait for reset
  }
  printLocalTime();
  
  // set up the ds 1307 RTC
  Wire.begin();
  
  // check if the RTC is connected to the I2C bus and it is accessible
  Wire.beginTransmission(DS1307_ADDRESS);
  err = Wire.endTransmission();
  if (err) {
    Serial.println("Could not find the DS1307 on the I2C bus\n");
    Serial.println("Please check the wiring\n");
    while (true)
      delay(100);
  }
  else
    Serial.print("DS1307 found on the I2C bus, all is ok ...\n");
  // set the register pointer to the beginning
  // This is the seconds register
  
  Wire.beginTransmission(DS1307_ADDRESS);
  seconds = bin2bcd(timeinfo.tm_sec);
  Serial.print("seconds: 0x");
  Serial.print(timeinfo.tm_sec,HEX);
  Serial.print(" in bcd: 0x");
  Serial.println(seconds,HEX);
  // Setting the seconds will also erase bit 8 of the seconds register
  // (CH = clock halt bit) and start the oscillator (see ds1307 data sheet)
  Wire.write(DS1307_TIME); // set the register pointer to the beginning of the time register section
  Wire.write(bin2bcd(timeinfo.tm_sec));    // write the seconds register
  Wire.write(bin2bcd(timeinfo.tm_min));    // write the minutes
  Wire.write(bin2bcd(timeinfo.tm_hour));   // this automatically selects 24h mode (bit 6 is low)
  Wire.write(bin2bcd(timeinfo.tm_wday+1)); // day in the week 
                                           // time info uses 0..6, ds1307 uses 1..7
  Wire.write(bin2bcd(timeinfo.tm_mday));   // day in the month
  Wire.write(bin2bcd(timeinfo.tm_mon+1));  // month: tm uses months 0..11, ds1307: 1..12
  unsigned int y = timeinfo.tm_year + 1900 - 2000; // timeinfo.tm_year gives me the number of years 
                                                      // since 1900                                                   
  Wire.write(bin2bcd((unsigned char)y));
  Wire.endTransmission(); 
}

void loop(){
}

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");  
  Serial.print("Day of week: ");
  Serial.println(&timeinfo, "%A");
  Serial.print("Month: ");
  Serial.println(&timeinfo, "%B");
  Serial.print("Day of Month: ");
  Serial.println(&timeinfo, "%d");
  Serial.print("Year: ");
  Serial.println(&timeinfo, "%Y");
  Serial.print("Hour: ");
  Serial.println(&timeinfo, "%H");
  Serial.print("Hour (12 hour format): ");
  Serial.println(&timeinfo, "%I");
  Serial.print("Minute: ");
  Serial.println(&timeinfo, "%M");
  Serial.print("Second: ");
  Serial.println(&timeinfo, "%S");

  Serial.println("Time variables");
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  Serial.println(timeHour);
  char timeWeekDay[10];
  strftime(timeWeekDay,10, "%A", &timeinfo);
  Serial.println(timeWeekDay);
  Serial.println();
}
