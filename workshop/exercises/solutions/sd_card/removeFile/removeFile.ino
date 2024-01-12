/**
 * removeFile.ino: removes the file /IoT4AQ/data/meas.txt as well as the
 * directories /IoT4AQ/data and IoT4AQ
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

int exists(fs::FS &fs, const char * dirname) {
  File root = fs.open(dirname);
  if(!root){
    Serial.println("Failed to open file");
    return(0);
  }
  if(root.isDirectory())  
    return(1);
  else
    return(-1);
}

void setup(){
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  // check if /IoT4AQ/data/meas.txt exists and is a normal file
  int retCode = exists(SD,"/IoT4AQ/data/meas.txt");
  if (retCode == DOES_NOT_EXIST) {
    Serial.println("/IoT4AQ/data/meas.txt does not exist");
    Serial.println("Nothing to be removed");
    while (true)
      delay(10);
  }
  else if (retCode == EXISTS_AS_DIR) {
    Serial.println("/IoT4AQ/data/meas.txt exists but is a directory");
    Serial.println("We do not touch it!");
    while (true)
      delay(10);
  }
  else if (retCode == EXISTS_AS_FILE) {
    Serial.println("/IoT4AQ/data/meas.txt exists and is a normal file");
    SD.remove("/IoT4AQ/data/meas.txt");
    SD.rmdir("/IoT4AQ/data");
    SD.rmdir("/IoT4AQ");
  }
}

void loop() {}
