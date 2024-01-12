/**
 * readFile.ino: reads simulated measurement data to a file on the SD card
 * The file is a text file residing in the root directory of the SD card
 * and is named meas.txt
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"

void setup(){

  Serial.begin(115200);
  while (!Serial)
    delay(10);
  
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  // try to open /meas.txt for reading

  File measFile = SD.open("/meas.txt");
  if(!measFile){
    Serial.println("Failed to open /meas.txt for reading");
    while (true)
      delay(100);
  }
  // Read the file and print its content
  while(measFile.available()){
    Serial.write(measFile.read());
  }
  measFile.close();
}

void loop() {}
