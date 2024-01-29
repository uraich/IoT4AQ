/**
 * pms5003.ino: reads the PlanTower PMS5003 dust sensor
 * Copyright (c) U. Raich Jan 2024
 * This program is part of the IoT4AQ workshop held at the 
 * University Aliound Diop, Bambey Sénégal 
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
  pms5003.printRaw(rawData);
  results = pms5003.evaluate(rawData);
  pms5003.printMsg(results);
  Serial.print("Checksum read: 0x");
  Serial.println(pms5003.readChecksum(rawData),HEX);
  Serial.print("Checksum calculated: 0x");
  Serial.println(pms5003.calcChecksum(rawData),HEX);
}

