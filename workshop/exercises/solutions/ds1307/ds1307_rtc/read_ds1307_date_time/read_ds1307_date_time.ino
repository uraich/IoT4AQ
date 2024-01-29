/**
 * ds1307_date_time.ino: Demostrates I2C access using the DS1307 RTC. 
 * Reads the first 8 bytes and extract the time information from it
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <string.h>
#include <stdio.h>

#define DS1307_ADDRESS 0x68
#define DS1307_TIME    0x00
#define TIME_SIZE         8

void setup() {
  byte err;
  char ds1307TimeBuf[TIME_SIZE];
  char *ds1307TimeBufPtr = ds1307TimeBuf;
  char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  char tmp[3];
  char valueTxt[10]; 
  int bytes_read = 0;
  Serial.begin(115200); // setup the serial line
  if (!Serial)
    delay(10);

  Wire.begin();
  // check if the RTC is connected to the I2C bus and it is accessible
  Wire.beginTransmission(DS1307_ADDRESS);
  err = Wire.endTransmission();
  if (err) {
    Serial.println("Could not find the DS1307 on the I2C bus\n");
    Serial.println("Please check the wiring\n");
    while (true)
      delay(100);
  }
  else
    Serial.print("DS1307 found on the I2C bus, all is ok ...\n");
  // set the register to 0x0 (start of Time information)
  // and read all the time informatio
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(DS1307_TIME); // write the register address
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_ADDRESS,TIME_SIZE); // ask for 8 bytes
  while (Wire.available()) {
      *ds1307TimeBufPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > TIME_SIZE)
	break;
    }
  Wire.endTransmission();
  if (err)
    Serial.println("Error when reading to the DS1307 Time regs");
  else {
    Serial.print(bytes_read);
    Serial.println(" characters read from the DS1307 Time regs");
  
    Serial.println("Time information from the DS1307 RTC");
    // point to the beginning of the array of result values
    ds1307TimeBufPtr = ds1307TimeBuf;

    for (int i=0;i<TIME_SIZE-1;i++) {
      sprintf(tmp,"%02x",*ds1307TimeBufPtr++);
      strcpy(valueTxt,"0x");
      strcat(valueTxt,tmp),
      strcat(valueTxt,", ");
      Serial.print(valueTxt);
      //Serial.print(*ds1307TimeBufPtr++,HEX);
      Serial.print("");
    }
    sprintf(tmp,"%02x",*ds1307TimeBufPtr++);
    strcpy(valueTxt,"0x");
    strcat(valueTxt,tmp),
    Serial.println();
    // Now evaluate the results
    ds1307TimeBufPtr = ds1307TimeBuf;
    // check if the clock is running
    if (*ds1307TimeBufPtr & 0x80)
      Serial.println("The clock is switched off");
    else
      Serial.println("The clock is running");
    // getting the seconds and printing them
    Serial.print("Seconds: ");
    Serial.print((*ds1307TimeBufPtr & 0x70) >> 4);
    Serial.println(*ds1307TimeBufPtr & 0xf);
    ds1307TimeBufPtr++;

    Serial.print("Minutes: ");
    Serial.print((*ds1307TimeBufPtr & 0x70) >> 4);
    Serial.println(*ds1307TimeBufPtr & 0xf);
    ds1307TimeBufPtr++;

    if (*ds1307TimeBufPtr & 0x40) {
      Serial.println("12h mode");
      Serial.print("Hours: ");
      Serial.print((*ds1307TimeBufPtr & 0x30)>>4);
      Serial.print(*ds1307TimeBufPtr & 0x4f);
      Serial.print(" ");
      if (*ds1307TimeBufPtr & 0x20) 
        Serial.println("pm");
      else
        Serial.println("am");
    }
    else {
      Serial.println("24h mode");
      Serial.print("Hours: ");
      Serial.print((*ds1307TimeBufPtr & 0x70) >> 4);
      Serial.println(*ds1307TimeBufPtr & 0xf);
    }  
  }
  ds1307TimeBufPtr++; 

  Serial.print("Day of the week: ");
  Serial.println(dayOfWeek[*ds1307TimeBufPtr-1]);
  ds1307TimeBufPtr++;

  Serial.print("Day: ");
  Serial.print((*ds1307TimeBufPtr & 0x30) >> 4);
  Serial.println(*ds1307TimeBufPtr & 0xf);
  ds1307TimeBufPtr++;

  Serial.print("Month: ");
  Serial.print((*ds1307TimeBufPtr & 0x10) >> 4);
  Serial.println(*ds1307TimeBufPtr & 0xf);
  ds1307TimeBufPtr++;

  Serial.print("Year: ");
  Serial.print(20);
  Serial.print(*ds1307TimeBufPtr >> 4);
  Serial.println(*ds1307TimeBufPtr &0xf);
}

void loop() {
}
