/**
 * set_ds3231_manual.ino: Sets the time on the ds3231 manually from a 
 * text string of the form: 17:36:25 Tue, Jan 09 2024
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include "time.h"

// constants needed to access the DS3231 RTC
#define DS3231_ADDRESS 0x68
#define DS3231_TIME    0x00
#define DS3231_CTRL    0x0e  // contains the control bit to switche the oscillator on or off
#define DS3231_STATUS  0x0f  // contains the OSF bit showing if the oscillator is or was off
#define OSCILLATOR_OFF 0x80

// The DS3231 uses bcd (binary coded decimal) encoding
// We must therefore convert the binary time values for seconds, minutes ...
// to bcd before sending them to the DS3231

unsigned char bin2bcd(unsigned char int_bin) {
  unsigned char high_nibble = int_bin / 10;
  unsigned char low_nibble  = int_bin % 10;
  return (high_nibble << 4) | low_nibble;
}

void setup(){
  unsigned char ds3231_ctrl, ds3231_status; 
  struct tm timeinfo;
  unsigned char seconds,minutes,hours;
  unsigned char day, month, year, dayOfWeek;
  char *monthStrings[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul",
    "Aug","Sep","Oct","Nov","Dec"};
  char *dayOfWeekStrings[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  // day, hours, minutes, seconds must be 2 characters to ease parsing
  char *timeString = "20:45:25 Tue, Feb 13 2024";
  char tmpString[5];
  unsigned int tmpInt;
  byte err;
  int i;

  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // Parse the time string
  tmpString[2]=0; // string ending zero
  tmpString[3]=0; // string ending zero
  tmpString[4]=0; // string ending zero

  tmpString[0] = timeString[0];
  tmpString[1] = timeString[1];
  sscanf(tmpString,"%02d",&tmpInt);
  hours = (unsigned char) tmpInt;

  tmpString[0] = timeString[3];
  tmpString[1] = timeString[4];
  sscanf(tmpString,"%02d",&tmpInt);
  minutes = (unsigned char) tmpInt;
  
  tmpString[0] = timeString[6];
  tmpString[1] = timeString[7];
  sscanf(tmpString,"%02d",&tmpInt);
  seconds = (unsigned char) tmpInt;

  // Serial.print(hours);
  // Serial.print(":");
  // Serial.print(minutes);
  // Serial.print(":");
  // Serial.println(seconds);
  
  strncpy(tmpString,&timeString[9],3);
  tmpString[3] = '\0';
  dayOfWeek = 8;      // allows to check if the correct entry has been found
  for (i=0;i<7;i++)
    if (!strcmp(tmpString,dayOfWeekStrings[i])) {
      dayOfWeek = i;
      break;
    }
  if (dayOfWeek == 8)
    Serial.println("day not found");

  Serial.print(tmpString);
  Serial.print(" ");
  Serial.print(dayOfWeek);
  Serial.print(" ");
  Serial.println(dayOfWeekStrings[dayOfWeek]);

  strncpy(tmpString,&timeString[14],3);
  // Serial.println(tmpString);
  for (i=0;i<12;i++)  
    if (!strcmp(tmpString,monthStrings[i])) {
      month = i+1;
      break;
    }
  // Serial.print("month: ");
  // Serial.println(month);

  tmpString[0] = timeString[18];
  tmpString[1] = timeString[19];
  tmpString[2] = 0;

  // Serial.print("day string: ");
  // Serial.println(tmpString);

  sscanf(tmpString,"%02d",&day);
  // Serial.print("day: ");
  // Serial.println(day);

  strncpy(tmpString,&timeString[21],4);
  // Serial.println(tmpString);
  sscanf(tmpString,"%04d",&tmpInt);
  year = (unsigned char) (tmpInt-2000);

  // Serial.print("year: ");
  // Serial.println(year);
 
  // set up the ds 1307 RTC
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

  // make sure the oscillator is swwitched on and the OSF flag is cleared

  if (ds3231_ctrl & OSCILLATOR_OFF) {
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(DS3231_CTRL);
    ds3231_ctrl &= ~OSCILLATOR_OFF;
    Serial.println("Oscillator  was off, switching it on");
    Wire.write(ds3231_ctrl);
    Wire.endTransmission();
  }
  if (ds3231_status & OSCILLATOR_OFF) {
    Wire.beginTransmission(DS3231_ADDRESS);
    Wire.write(DS3231_STATUS);
    ds3231_status &= ~OSCILLATOR_OFF;
    Serial.println("Oscillator status shows off, resetting the flag");
    Wire.write(ds3231_status);
    Wire.endTransmission();    
  }
  
  // set the register pointer to the beginning
  // This is the seconds register
  
  Wire.beginTransmission(DS3231_ADDRESS);

  Wire.write(DS3231_TIME);          // set the register pointer to the beginning of the time register section
  Wire.write(bin2bcd(seconds));     // write the seconds register
  Wire.write(bin2bcd(minutes));     // write the minutes
  Wire.write(bin2bcd(hours));       // this automatically selects 24h mode (bit 6 is low)

  Wire.write(bin2bcd(dayOfWeek+1)); // day in the week 
                                    // time info uses 0..6, ds3231 uses 1..7
  Wire.write(bin2bcd(day));         // day in the month
  Wire.write(bin2bcd(month));       // month: tm uses months 0..11, ds3231: 1..12
  Wire.write(bin2bcd(year));

  Wire.endTransmission();

  Serial.print("Time and date set to: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.print(seconds);
  Serial.print(" ");
  Serial.print(day);
  Serial.print("/");
  Serial.print(month);
  Serial.print("/");
  Serial.println(year);
}

void loop(){
}
