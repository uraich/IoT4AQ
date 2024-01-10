/**
 * readESP32RTC.ino: Reads time and date from the ESP32 RTC and 
 * prints it
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <ESP32Time.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  ESP32Time esp32RTC;
  Serial.print(esp32RTC.getTime("%A, %B %d %Y %H:%M:%S"));
}

void loop() {}
