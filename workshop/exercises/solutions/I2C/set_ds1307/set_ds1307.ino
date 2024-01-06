// set_ds1307.ino: Read the date and time from ntp and set the ds1307
// real time clock
// Copyright (c) U. Raich
// This program is part of the IoT4AQ workshop at the
// University Alioune Diop, Bambey, Sénégal, 2024
// It is released under the MIT license

#include <WiFi.h>
#include <NTPClient.h>

#include "RTClib.h"
rtc_ds1307 RTC;     // Setup an instance of DS1307 RTC class

const char *ssid     = "WLAN18074253";
const char *password = "Q4k6V35sFauw";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP);

void setup() {
  Serial.begin(115200);
  /* connect to wifi and wait until connection established */
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  /* get time and date */
  timeClient.begin();
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
}

void loop() {
}
