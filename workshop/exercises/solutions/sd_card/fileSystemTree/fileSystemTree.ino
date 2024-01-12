/**
 * fileSytemTree.ino: Walks the file system tree and prints all the files
 * in directories and sub-directories ...
 * listDir was essentially copied from the ESP32 SD library examples
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.print("Listing directory: ");
    Serial.println(dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(10);
 
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  // walk the file system up to a depth of 3
  listDir(SD, "/", 3);
  while (true)
    delay(100);
}

void loop() {

}
