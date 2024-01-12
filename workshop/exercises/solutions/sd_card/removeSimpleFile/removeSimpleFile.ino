/**
 * removeSimpeFile.ino: removes the file /meas.txt from the SD card
 * if it exists
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <string.h>

#define EXISTS_AS_FILE -1
#define DOES_NOT_EXIST  0
#define EXISTS_AS_DIR   1

void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  File measFile = SD.open("/meas.txt");
  if (!measFile) {
    Serial.println("/meas.txt does not exist on the SD card");
    Serial.println("There is nothing to remove");
    while (true)
      delay(100);
  }
  else {
    SD.remove("/meas.txt");
    Serial.println("/meas.txt has been deleted from the SD card");
  }
}

void loop() {}
