/**
 * ds1307RAM.ino: Demostrates I2C access using the DS1307 RTC. 
 * The RTC has 56 bytes of battery backed up RAM that can be written and read
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Wire.h>
#include <string.h>

#define DS1307_ADDRESS 0x68
#define DS1307_NVRAM   0x08
void setup() {
  byte err;
  char *testText = "Welcome to the IoT4AQ workshop, Bambey 2024\n";

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
  // set the register to 0x08 (start of NVRAM)
  // and write all the characters of the testText into the RAM

  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(DS1307_NVRAM); // write the register address
  
  for (int i=0;i<strlen(testText);i++)
    Wire.write(testText[i]);
  Wire.write(0);

  Wire.endTransmission();
  if (err)
    Serial.println("Error when writing to the DS1307 NVRAM\n");
  else
  Serial.println("Text successfully written to the DS1307 NVRAM\n");
}
void loop() {
}
