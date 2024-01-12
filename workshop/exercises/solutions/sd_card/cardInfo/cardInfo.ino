/**
 * cardInfo.ino: Gets all relevant information on the SD card inserted into 
 * the SD card slot and prints it.
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
  uint8_t cardType;
  uint64_t cardSize;
  size_t numSectors;
  size_t sectorSize;
  size_t totalBytes;
  size_t usedBytes;
    
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }
  
  // The SD card works with the SPI bus who's pin definitions for your
  // ESP32 CPU card can be found in the variants directory of .arduino15
  // For the TTGO ESP32 T7 v1.3 you find it at
  // ~/.arduino15/packages/esp32/hardware/esp32/2.0.11/variants/ttgo-t7-v13-mini32/pins_arduino.h
  
  Serial.println("Pin definitions of SPI bus:");
  Serial.print("Chip Select (SS): ");
  Serial.println(SS);
  Serial.print("MOSI: "); // master out slave in
  Serial.println(MOSI);
  Serial.print("MISO: "); // master in slave out
  Serial.println(MISO);
  Serial.print("SCK: ");  // the clock signal
  Serial.println(SCK);
  
  cardType = SD.cardType();
  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }
  cardSize = SD.cardSize() / (1024 * 1024); // card size in GBytes
  Serial.print("The card has a total size of ");
  Serial.print(cardSize);
  Serial.println(" GBytes");
  totalBytes = SD.totalBytes();
  usedBytes = SD.usedBytes();
  Serial.print("More precisely, it has a total of ");
  Serial.print(totalBytes);
  Serial.print(" Bytes, of which ");
  Serial.print(usedBytes);
  Serial.println(" are used");
  numSectors = SD.numSectors();
  sectorSize = SD.sectorSize();
  Serial.print("This corresponds to ");
  Serial.print(numSectors);
  Serial.print(" sectors with a sector size of ");
  Serial.print(sectorSize);
  Serial.println(" Bytes each");
}

void loop() {}

