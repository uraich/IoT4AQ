/**
 * ds1307RAM.ino: Demostrates I2C how to write the ds1307 RAM using methods
 * from the rtclib
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <RTClib.h>
#include <string.h>

#define NVRAM_BEGIN 0

void setup() {
  byte err;
  char *testText = "Welcome to the IoT4AQ workshop, Bambey 2024\n";
  // define an RTC_DS1307 instance
  RTC_DS1307 ds1307;

  Serial.begin(115200); // setup the serial line
  if (!Serial)
    delay(10);

  // check if ds1307 is connected and accessible
  if (!ds1307.begin()) {
    Serial.println("Could not find ds1307 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }
  ds1307.writenvram(NVRAM_BEGIN,(const uint8_t *) testText,strlen(testText));
  // write the string terminating zero
  // This makes it easier to read the text back
  ds1307.writenvram(strlen(testText),0);
  Serial.println("ds1307 NVRAM has been written");
}
void loop() {
}
