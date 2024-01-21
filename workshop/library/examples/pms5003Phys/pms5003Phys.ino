/**
 * pms5003Phys.ino: Reads the raw data from the PMS5003 protocol
 * Converts the raw data into physical values and prints them
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <PMS5003.h>
PMS5003 pms5003 = PMS5003(); // initialize the PMS5003 class

void setup() {
  Serial.begin(115200);
  if (!Serial)
    delay(10);
}

void loop() {
  uint8_t *rawData;
  pms5003Data *results;
  rawData = pms5003.readRaw();
  results = pms5003.evaluate(rawData);
  pms5003.printMsg(results);
  delay(1000);
}
  
