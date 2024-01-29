/**
 * ds1307ToESP32RTC.ino: The program reads time and date from the ds1307
 * time registers and copies the values to the ESP32RTC.
 * The ds1307 registers are non-volatile (battery backed-up) and time is
 * kept, even if the ESP32 is not powered.
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>       // gives access to the I2C functions
#include <ESP32Time.h>  // time functions using the ESP32 RTC

// constants needed to access the DS1307 RTC
#define DS1307_ADDRESS 0x68  // I2C address of ds1307
#define DS1307_TIME    0x00  // Register address where the time information starts
#define TIME_SIZE         8  // number of registers used to store time information
#define CH             0x80  // oscillator enabled
#define _12H_MODE      0x40  // bit defining is hour is given in 12h + am/pm or 24h mode
                             // if set: 12h mode
#define AM_PM          0x20  // if set: pm

// convert from BCD to binary representation
int bcd2bin(unsigned char bcd_value) {
  unsigned char high_nibble = bcd_value >> 4;
  unsigned char low_nibble = bcd_value & 0xf;
  return (int) (high_nibble * 10 + low_nibble);
}

void setup() {
  unsigned char ds1307TimeBuf[TIME_SIZE];
  unsigned char *ds1307TimeBufPtr;
  unsigned char tmp;
  int year, month,day,hours,minutes,seconds,dayOfWeek; // setTime expects int values
  int bytes_read;
  byte err;
  
  Serial.begin(115200);
  if (!Serial)
    delay(10);

  // check if the RTC is connected to the I2C bus and it is accessible
  Wire.begin();
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

  // get the time information from the DS1307
  Wire.requestFrom(DS1307_ADDRESS,TIME_SIZE); // ask for 8 bytes
  ds1307TimeBufPtr = ds1307TimeBuf;
  bytes_read = 0;
  while (Wire.available()) {
      *ds1307TimeBufPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > TIME_SIZE)
	break;
    }
  Wire.endTransmission();
  /* for debugging only
  // print raw values
  ds1307TimeBufPtr = ds1307TimeBuf;
  for (int i=0;i<7;i++) {
    Serial.print("0x");
    Serial.print(*ds1307TimeBufPtr++,HEX);
    Serial.print(" ");
  }
  Serial.println();
  */
  // convert the register values to those needed by setTime of ESP32Time
  // which sets the time in the ESP32RTC
  // Converts the values from BCD to binary representation

  ds1307TimeBufPtr = ds1307TimeBuf;
  if (*ds1307TimeBufPtr & CH) {
    Serial.println("Oscillator is switched of and RTC not running");
    Serial.println("Setting the ESP32 RTC with these time values makes no sense!");
    while (true)
      delay(100); // wait for correction and reset
  }
      
  seconds = bcd2bin(*ds1307TimeBufPtr++ & 0x7f);
  minutes = bcd2bin(*ds1307TimeBufPtr++ & 0x7f);
  tmp = *ds1307TimeBufPtr++ & 0x7f;
  if (tmp & _12H_MODE) {        // if bit 6 is set, 12 h mode is selected
    if (tmp & AM_PM)
      hours = bcd2bin(tmp & 0x1f) + 12;
    else
      hours = bcd2bin(tmp & 0x1f);
  }
  else
    hours   = bcd2bin(tmp & 0x3f);
  dayOfWeek = bcd2bin(*ds1307TimeBufPtr++ & 0x7);
  day       = bcd2bin(*ds1307TimeBufPtr++ & 0x3f);
  month     = bcd2bin(*ds1307TimeBufPtr++ & 0x1f);
  year      = bcd2bin(*ds1307TimeBufPtr) + 2000;
    
  Serial.print("Setting the ESP32 RTC with the following date & time: ");
  Serial.print(day);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.print(year);
  Serial.print(" ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
    
  // initialize ESP32Time
  ESP32Time esp32RTC;
  // set the time and date
  esp32RTC.setTime(seconds, minutes, hours, day, month, year);
  // read back time and date from the ESP32 RTC
  Serial.print("Read back from the ESP32 RTC for confirmation: ");
  Serial.println(esp32RTC.getTime("%A, %B %d %Y %H:%M:%S"));
}

void loop() {
}
