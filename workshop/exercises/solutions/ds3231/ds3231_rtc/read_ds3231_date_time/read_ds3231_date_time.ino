/**
 * ds3231_date_time.ino: Demostrates I2C access using the DS3231 RTC.
 * Reads the control and status registers and checks if the oscillator
 * is on 
 * Reads the first 8 bytes and extract the time information from it
 * Reads the temperature raw values and calculates the temperature in °C
 * from it
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <string.h>
#include <stdio.h>

#define DS3231_ADDRESS 0x68
#define DS3231_TIME    0x00
#define DS3231_CTRL    0x0e
#define DS3231_TEMP    0x11
#define TIME_SIZE         8
#define CTRL_SIZE         2
#define TEMP_SIZE         2

#define OSCILLATOR_EN  0x80
#define BBSQW          0x40

void setup() {
  byte err;
  char ds3231TimeBuf[TIME_SIZE];
  char *ds3231TimeBufPtr = ds3231TimeBuf;
  char ds3231CtrlBuf[CTRL_SIZE];
  char *ds3231CtrlBufPtr = ds3231CtrlBuf;
  char ds3231TempBuf[CTRL_SIZE];
  char *ds3231TempBufPtr = ds3231TempBuf; 
  int16_t temp;
  float temperature;

  char *dayOfWeek[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  char tmp[3];
  char valueTxt[10]; 
  int bytes_read;
  Serial.begin(115200); // setup the serial line
  if (!Serial)
    delay(10);

  Wire.begin();
  // check if the RTC is connected to the I2C bus and it is accessible
  Wire.beginTransmission(DS3231_ADDRESS);
  err = Wire.endTransmission();
  if (err) {
    Serial.println("Could not find the DS3231 on the I2C bus\n");
    Serial.println("Please check the wiring\n");
    while (true)
      delay(100);
  }
  else
    Serial.print("DS3231 found on the I2C bus, all is ok ...\n");

  // read the control and status register
  // set the register to 0x0e, the control register
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(DS3231_CTRL); // write the register address
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS,CTRL_SIZE); // ask for 2 bytes
  bytes_read = 0;
  while (Wire.available()) {
      *ds3231CtrlBufPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > CTRL_SIZE)
	break;
    }
  Wire.endTransmission();
  if (err)
    Serial.println("Error when reading to the DS3231 Ctrl regs");
  else {
    Serial.println("---------------------------------------------------");
    Serial.print(bytes_read);
    Serial.println(" characters read from the DS3231 CTRL regs");


    // check if the clock is running
    if (ds3231CtrlBuf[0] & OSCILLATOR_EN)
      Serial.println("Oscillator is switched off");
    else
      Serial.println("Oscillator is switched on");
    if (ds3231CtrlBuf[1] & OSCILLATOR_EN)
       Serial.println("Oscillator is or was switched off");
    else
      Serial.println("Oscillator was never switched off");
  }    
  // set the register to 0x0 (start of Time information)
  // and read all the time informatio
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(DS3231_TIME); // write the register address
  Wire.endTransmission();
 
  Wire.requestFrom(DS3231_ADDRESS,TIME_SIZE); // ask for 8 bytes
  bytes_read = 0;
  while (Wire.available()) {
      *ds3231TimeBufPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > TIME_SIZE)
	break;
    }
  Wire.endTransmission();
  if (err)
    Serial.println("Error when reading to the DS3231 Time regs");
  else {
    Serial.println("---------------------------------------------------");
    Serial.print(bytes_read);
    Serial.println(" characters read from the DS3231 Time regs");
  
    Serial.println("Time information from the DS3231 RTC");
    // point to the beginning of the array of result values
    ds3231TimeBufPtr = ds3231TimeBuf;

    for (int i=0;i<TIME_SIZE-1;i++) {
      sprintf(tmp,"%02x",*ds3231TimeBufPtr++);
      strcpy(valueTxt,"0x");
      strcat(valueTxt,tmp),
      strcat(valueTxt,", ");
      Serial.print(valueTxt);
      //Serial.print(*ds3231TimeBufPtr++,HEX);
      Serial.print("");
    }
    sprintf(tmp,"%02x",*ds3231TimeBufPtr++);
    strcpy(valueTxt,"0x");
    strcat(valueTxt,tmp),
    Serial.println();
    // Now evaluate the results
    ds3231TimeBufPtr = ds3231TimeBuf;
    // getting the seconds and printing them
    Serial.print("Seconds: ");
    Serial.print((*ds3231TimeBufPtr & 0x70) >> 4);
    Serial.println(*ds3231TimeBufPtr & 0xf);
    ds3231TimeBufPtr++;

    Serial.print("Minutes: ");
    Serial.print((*ds3231TimeBufPtr & 0x70) >> 4);
    Serial.println(*ds3231TimeBufPtr & 0xf);
    ds3231TimeBufPtr++;

    if (*ds3231TimeBufPtr & 0x40) {
      Serial.println("12h mode");
      Serial.print("Hours: ");
      Serial.print((*ds3231TimeBufPtr & 0x30)>>4);
      Serial.print(*ds3231TimeBufPtr & 0x4f);
      Serial.print(" ");
      if (*ds3231TimeBufPtr & 0x20) 
        Serial.println("pm");
      else
        Serial.println("am");
    }
    else {
      Serial.println("24h mode");
      Serial.print("Hours: ");
      Serial.print((*ds3231TimeBufPtr & 0x70) >> 4);
      Serial.println(*ds3231TimeBufPtr & 0xf);
    }  
  }
  ds3231TimeBufPtr++; 

  Serial.print("Day of the week: ");
  Serial.println(dayOfWeek[*ds3231TimeBufPtr-1]);
  ds3231TimeBufPtr++;

  Serial.print("Day: ");
  Serial.print((*ds3231TimeBufPtr & 0x30) >> 4);
  Serial.println(*ds3231TimeBufPtr & 0xf);
  ds3231TimeBufPtr++;

  Serial.print("Month: ");
  Serial.print((*ds3231TimeBufPtr & 0x10) >> 4);
  Serial.println(*ds3231TimeBufPtr & 0xf);
  ds3231TimeBufPtr++;

  Serial.print("Year: ");
  Serial.print(20);
  Serial.print(*ds3231TimeBufPtr >> 4);
  Serial.println(*ds3231TimeBufPtr &0xf);

  // Read the temperature
  Wire.beginTransmission(DS3231_ADDRESS);
  Wire.write(DS3231_TEMP); // write the register address
  Wire.endTransmission();
  Wire.requestFrom(DS3231_ADDRESS,TEMP_SIZE); // ask for 2 bytes
  bytes_read = 0;
  while (Wire.available()) {
      *ds3231TempBufPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > TEMP_SIZE)
	break;
    }
  Wire.endTransmission();
  if (err)
    Serial.println("Error when reading to the DS3231 Temperature regs");
  else {
    Serial.println("---------------------------------------------------");
    Serial.print(bytes_read);
    Serial.println(" characters read from the DS3231 Temperature regs");
    Serial.print("Temperature msb register: 0x");
    Serial.println(ds3231TempBuf[0],HEX);
    Serial.print("Temperature lsb register: 0x");
    Serial.println(ds3231TempBuf[1],HEX);

    // decode the temperature
    if (ds3231TempBuf[0] & 0x80) { // the temperature is negative 
      temp = -((ds3231TempBuf[0] << 8) | ds3231TempBuf[1]);
      temperature = (float) (temp >> 8) + (float)((temp & 0x0c) >> 6)* 0.25;
    } 
    else  // temperature is positive
      temperature = (float) ds3231TempBuf[0] + (float)(ds3231TempBuf[1] >> 6) * 0.25;

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }
}

void loop() {
}
