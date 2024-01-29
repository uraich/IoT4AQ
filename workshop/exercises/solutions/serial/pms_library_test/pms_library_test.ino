/**
 * pms_library_test.ino: Reads the PlanTower PMS5003 using the PMS_Library
 * library
 * It uses the library function readMeas() which returns a data structure
 * containing the results
 *
 * Copyright (c)  Uli Raich, January 2024
 * This program is part of the IoT4AQ workshop
 * held at the university Alioune Diop, Bambey, Sénégal
 * 
 * License: MIT
 */

#include "PMS.h"

PMS pms(Serial2);
PMS::DATA data;

void setup()
{
  Serial.begin(115200);                  // UART0
  Serial2.begin(9600,SERIAL_8N1,34,22);  // UART2 on Rx GPIO 34, Tx GPIO 33 
}

void loop()
{
  if (pms.read(data))
  {
    Serial.print("PM 1.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_1_0);

    Serial.print("PM 2.5 (ug/m3): ");
    Serial.println(data.PM_AE_UG_2_5);

    Serial.print("PM 10.0 (ug/m3): ");
    Serial.println(data.PM_AE_UG_10_0);

    Serial.println();
  }

  // Do other stuff...
}
