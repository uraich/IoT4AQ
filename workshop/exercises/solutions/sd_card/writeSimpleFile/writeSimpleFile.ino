/**
 * writeSimpleFile.ino: writes some text to a file on the SD card
 * The file resides on the root directory of the SD card and is named meas.txt
 * If the file exists, the text is appended appended
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <ESP32Time.h>
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
  if(root.isDirectory()){
    Serial.println("Is a directory");
    return(1);
  }
  else
    return(-1);
}

void setup(){
  Serial.begin(115200);
  if (!Serial)
    delay(10);
  FILE root;
  File measFile;
  char *measTxt = "Welcome the the IoT4AQ workshop\nIt is held at the Alioune Diop University Bambey (UADB), Sénégal, March 2024\n";
  
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  // check if /meas exists and is a normal text file
  int retCode = exists(SD,"/meas.txt");
  if (retCode == EXISTS_AS_DIR) {
    Serial.println("/meas exists but is a directory");
    while (true)
      delay(100); // we do not want to overwrite this file, so be better stop here
  }
  else if (retCode == DOES_NOT_EXIST) {
    Serial.println("/meas.txt does not exist");
    // create the file and write the time stamp and meas string
    measFile = SD.open("/meas.txt",FILE_WRITE);
    if(!measFile){
      Serial.println("Failed to open /meas.txt for writing");
      while (true)
        delay(100);
    }
    Serial.println("Created a new file /meas.txt");
  }
  else if (retCode == EXISTS_AS_FILE) {
    // the file exists, we therefore open it in append mode
    measFile = SD.open("/meas.txt",FILE_APPEND);
    if(!measFile){
      Serial.println("Failed to open /meas.txt for appending");
      while (true)
        delay(100);
    }
    Serial.println("Appending to file meas.txt");  
  }
  // now that we managed to open the file, lets write the text
  
  measFile.print(measTxt);
  Serial.print(measTxt);
  Serial.println("written to file /meas.txt");
  measFile.close();
}

void loop() {}