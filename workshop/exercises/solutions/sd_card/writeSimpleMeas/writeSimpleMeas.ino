/**
 * writeSimpleFile.ino: writes temperature and humidity measurement data 
 * to a file on the SD card
 * The file resides on the root directory of the SD card and is named meas.txt
 * If the file exists, the simulated measurement data are appended
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
#include "setTimeNTP.h"
#include <DHT11.h>

#define EXISTS_AS_FILE -1
#define DOES_NOT_EXIST  0
#define EXISTS_AS_DIR   1

#define DHT11_DATALINE 16
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
  FILE root;
  ESP32Time esp32RTC;
  setTimeNTP(); // set up the RTC on the ESP32 RTC and the ds1307
  File measFile;
  String timeStamp = esp32RTC.getDateTime();
  int temperature, humidity;
  char measTxt[100];
  
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  
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
  // read temperature and humidiy
  // the way the library is designed we have to wait 1 s between the two
  // measurements
  DHT11 dht11(DHT11_DATALINE);
  temperature = dht11.readTemperature();
  // now that we managed to open the file, lets write the time stamp
  // and the measurement data
  delay(1000);
  humidity = dht11.readHumidity();

  // Check the results of the readings.
  // If there are errors print its type
  // if no errors are detected, print the temperature and humidity values in CSV format.
  if ((temperature == DHT11::ERROR_CHECKSUM) || (temperature == DHT11::ERROR_TIMEOUT))
    Serial.println(dht11.getErrorString(temperature));
  else if ((humidity == DHT11::ERROR_CHECKSUM) || (humidity == DHT11::ERROR_TIMEOUT))
    Serial.println(dht11.getErrorString(humidity));
  else {  
    measFile.print(timeStamp.c_str());
    sprintf(measTxt,", Temperature: %d°C, Humidity: %d%% ",temperature,humidity);
    Serial.print(timeStamp.c_str());
    Serial.print(measTxt);
    Serial.println(" written to file /meas.txt");
  }
  measFile.close();
}

void loop() {}
