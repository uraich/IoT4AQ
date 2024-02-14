/**
 * read_ds3231_date_time.ino: The program reads time and date from the ds3231
 * time registers and prints its using methods of the DateTime class 
 * provided by RTClib
 * The ds3231 registers are non-volatile (battery backed-up) and time is
 * kept, even if the ESP32 is not powered.
 * This program uses the RTClib to access the ds3231
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>       // gives access to the I2C functions
#include <RTClib.h>
#include <ESP32Time.h>  // time functions using the ESP32 RTC

void setup() {
  RTC_DS3231 ds3231;
  DateTime now;
  
  Serial.begin(115200);
  if (!Serial)
    delay(10);

  // check if ds3231 is connected and accessible
  if (!ds3231.begin()) {
    Serial.println("Could not find ds3231 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }
  // check if the OSF flag is set, in which case the date and time might be wrong
  if (ds3231.lostPower()) {
    Serial.println("DS3231 Oscillator is or was switched off");
    Serial.println("Please run a program to set the DS3231, which switches the oscillator on");
    while (true)
      delay(100);
  }
  // get the time from the ds3231 using the RTClib now() method
  // this returns a DateTime object which can be printed using the
  // toString() method
  
  now = ds3231.now();
  char timeFormat[] = "DDD DD.MMM YYYY hh:mm:ss";
  
  Serial.print("The current date and time on the DS3231: ");
  Serial.println(now.toString(timeFormat));
}

void loop() {
}
