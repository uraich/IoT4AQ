/**
 * ds1307ToESP32RTC.ino: The program reads time and date from the ds1307
 * time registers and copies the values to the ESP32RTC.
 * The ds1307 registers are non-volatile (battery backed-up) and time is
 * kept, even if the ESP32 is not powered.
 * This program uses the RTClib to access the ds1307
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
  RTC_DS1307 ds1307;
  ESP32Time esp32RTC;
  DateTime now;

  Serial.begin(115200);
  if (!Serial)
    delay(10);

  // check if ds1307 is connected and accessible
  if (!ds1307.begin()) {
    Serial.println("Could not find ds1307 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }  
  if (!ds1307.isrunning()) {
    Serial.println("DS1307 Oscillator is switched off");
    Serial.println("Please run a program to set the DS1307, which switches the oscillator on");
    while (true)
      delay(100);
  }
  // get the time from the ds1307 using the RTClib now() method
  // this returns a DateTime object which can be printed using the
  // toString() method
  
  now = ds1307.now();
  char timeFormat[] = "DDD DD.MMM YYYY hh:mm:ss";
  
  Serial.print("The current date and time on the DS1307: ");
  Serial.println(now.toString(timeFormat));
  Serial.println("Setting the ESP32 RTC with this time");
  esp32RTC.setTime((int) now.second(),
		   (int) now.minute(),
		   (int) now.hour(),
		   (int) now.day(),
		   (int) now.month(),
		   (int) now.year());
  // read back time and date from the ESP32 RTC
  Serial.print("Read back from the ESP32 RTC for confirmation: ");
  Serial.println(esp32RTC.getTime("%A, %B %d %Y %H:%M:%S"));
}

void loop() {
}
