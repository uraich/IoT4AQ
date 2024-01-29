/**
 * ds1307RAM.ino: Demostrates I2C access using the DS1307 RTC. 
 * The RTC has 56 bytes of battery backed up RAM that can be written and read
 * This version uses the RTClib
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <RTClib.h>
#include <string.h>

#define NVRAM_SIZE       56
#define NVRAM_BEGIN       0

void setup() {
  
  byte err;
  uint8_t nvramContent[NVRAM_SIZE];
  uint8_t *nvramContentPtr;
  int bytes_read = 0;
  RTC_DS1307 ds1307;
  
  // check if ds1307 is connected and accessible
  if (!ds1307.begin()) {
    Serial.println("Could not find ds1307 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }
  
  Serial.begin(115200); // setup the serial line
  if (!Serial)
    delay(10);

  // Read the nvram
  ds1307.readnvram(nvramContent,NVRAM_SIZE,NVRAM_BEGIN);
  nvramContentPtr = nvramContent;
  /* 
  for (int i=0;i<10;i++) {
    Serial.print(*nvramContentPtr++,HEX);
    Serial.print(" ");
  }
  Serial.println();
  */
  Serial.println("Read from the ds1307 NVRAM:");
  Serial.print((char *) nvramContent);
}

void loop() {
}
