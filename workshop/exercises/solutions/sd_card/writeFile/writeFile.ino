/**
 * writeFile.ino: writes simulated measurement data to a file on the SD card
 * The file is a text file residing in a directory Iot4AQ/data 
 * and is named meas.txt
 * If the directories do not exist, they are created
 * If the file does not exist, it is created, otherwise the data are appended
 * to the existing file
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <RTClib.h>
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
  if(!root.isDirectory()){
    // Serial.println("Not a directory");
    return(-1);
  }
  else
    return(1);
}

int createDir(fs::FS &fs, const char * path){
    Serial.print("Creating Dir: ");
    Serial.println(path);
    if(fs.mkdir(path)){
      Serial.println("Directory successfully created");
      return(1);
    } 
    else {
      Serial.println("mkdir failed");
      return(-1);
    }
}

void setup(){
  FILE root;
  char *measTxt = "Welcome the the IoT4AQ workshop\nIt is held at the Alioune Diop University Bambey (UADB), Sénégal, March 2024\n";

  Serial.begin(115200);
  if (!Serial)
    delay(10);
  
  if(!SD.begin()){
    Serial.println("Card Mount Failed");
    return;
  }

  // check if /IoT4AQ exists and is a directory
  int retCode = exists(SD,"/IoT4AQ");
  if (retCode == DOES_NOT_EXIST) {
    Serial.println("/IoT4AQ does not exist");
    // create the directory since it does not exist
    if (createDir(SD,"/IoT4AQ") > 0)
      Serial.println("/IoT4AQ successfully created");
    else {
      Serial.println("Creating /IoT4AQ failed, giving up...");
      while (true)
        delay(100);
    }
  }
  else if (retCode == EXISTS_AS_FILE) {
    Serial.println("/IoT4AQ exists but is a normal file");
    while (true)
      delay(100); // we do not want to overwrite this file, so be better stop here
  }
  else if (retCode == EXISTS_AS_DIR)
    Serial.println("/IoT4AQ exists and is a directory");

  // check if /IoT4AQ/data exists and is a directory
  retCode = exists(SD,"/IoT4AQ/data");
  if (retCode == DOES_NOT_EXIST) {
    Serial.println("/IoT4AQ/data does not exist");
      // create the directory since it does not exist
    if (createDir(SD,"/IoT4AQ/data") > 0)
      Serial.println("/IoT4AQ/data successfully created");
    else {
      Serial.println("Creating /IoT4AQ/data failed, giving up...");
      while (true)
        delay(100);
    }
  }
  else if (retCode == EXISTS_AS_FILE) 
    while (true)
      delay(100); // we do not want to overwrite this file, so we better stop here
  
  else if (retCode == EXISTS_AS_DIR)
    Serial.println("/IoT4AQ/data exists and is a directory");

  // check if /IoT4AQ/data/meas.txt exists and is a normal file
  retCode = exists(SD,"/IoT4AQ/data/meas.txt");
  if (retCode == DOES_NOT_EXIST) {
    Serial.println("/IoT4AQ/data/meas.txt does not exist");
    // create the file and write the simulated measurement data
    File measFile = SD.open("/IoT4AQ/data/meas.txt",FILE_WRITE);
    if(!measFile){
      Serial.println("Failed to open /IoT4AQ/data/meas.txt for writing");
      while (true)
        delay(100);
    }
    else {
      measFile.print(measTxt);
      Serial.print(measTxt);
      Serial.println(" written to new file /IoT4AQ/data/meas.txt");
      measFile.close();
    }
  }
  else if (retCode == EXISTS_AS_DIR) {
    Serial.println("/IoT4AQ/data/meas.txt exists but is a directory");
    while (true)
      delay(100);
  }
  else if (retCode == EXISTS_AS_FILE) {
    Serial.println("/IoT4AQ/data/meas.txt exists and is a normal file");
    File measFile = SD.open("/IoT4AQ/data/meas.txt",FILE_APPEND);
    if(!measFile){
      Serial.println("Failed to open /IoT4AQ/data/meas.txt for appending");
      while (true)
        delay(100);
    }
    else {
      measFile.print(measTxt);
      Serial.print(measTxt);
      Serial.println(" appended to file /IoT4AQ/data/meas.txt");
      measFile.close();
    }
  }
}

void loop() {}