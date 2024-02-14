/**
 * set_ds3231_manual.ino: Sets the time on the ds3231 manually from a 
 * text string of the form: 17:36:25 Tue, Jan 09 2024
 * Passes through the RTClib to accomplish this
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <RTClib.h>
#include "time.h"

void setup(){
  uint8_t seconds,minutes,hours;
  uint8_t day, month, dayOfWeek;
  uint16_t year;
  char *monthStrings[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul",
    "Aug","Sep","Oct","Nov","Dec"};
  char *dayOfWeekStrings[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
  // day, hours, minutes, seconds must be 2 characters to ease parsing
  char *timeString = "17:36:25 Tue, Jan 09 2024";
  char tmpString[5];
  unsigned int tmpInt;
  int i;
  RTC_DS3231 ds3231;
  
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // check if ds3231 is connected and accessible
  if (!ds3231.begin()) {
    Serial.println("Could not find ds3231 on the I2C bus");
    Serial.println("Please check the wiring");
    while (true)
      delay(100); // wait for correction and reset
  }  

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
  
  // This is not needed but kept for compatibility with the version 
  // not using RTClib
  strncpy(tmpString,&timeString[9],3);
  dayOfWeek = 8;      // allows to check if the correct entry has been found
  for (i=0;i<7;i++)
    if (!strcmp(tmpString,dayOfWeekStrings[i])) {
      dayOfWeek = i;
      break;
    }
  if (dayOfWeek == 8)
    Serial.println("dayOfWeekString not found");
  // Serial.print(tmpString);
  // Serial.print(" ");
  // Serial.println(dayOfWeek);

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
  year = tmpInt;

  // Serial.print("year: ");
  // Serial.println(year);
  
  ds3231.adjust(DateTime(year,month,day,hours,minutes,seconds));

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
