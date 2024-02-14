/* setESP32RTC.cpp: Reads the time form the DS3231 and sets the 
 * ESP32 RTC
 * Copyright (c) U. Raich, Jan. 2024
 * This program is part of the IoT4AQ workshop held at the 
 * University Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

 #include "setESP32RTC.h"
extern ESP32Time esp32RTC;

void setESP32RTC(void) {
  RTC_DS3231 ds3231;
  DateTime now;

    // check if ds3231 is connected and accessible
  if (!ds3231.begin()) {
    Serial.println("Could not find ds3231 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }  
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
  Serial.println("Setting the ESP32 RTC with this time");
  esp32RTC.setTime((int) now.second(),
		   (int) now.minute(),
		   (int) now.hour(),
		   (int) now.day(),
		   (int) now.month(),
		   (int) now.year());
  // read back time and date from the ESP32 RTC
  Serial.print("Read back from the ESP32 RTC for confirmation: ");
  //Serial.println(esp32RTC.getTime("%A, %B %d %Y %H:%M:%S"));  
  Serial.println(esp32RTC.getTime("%H:%M:%S %d %b %Y"));
}
