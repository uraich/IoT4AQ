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
#define NVRAM_SIZE       56

void setup() {
  byte err;
  char ds1307Text[NVRAM_SIZE];
  char *ds1307TextPtr = ds1307Text;
  
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
  // set the register to 0x08 (start of NVRAM)
  // and read the entire NVRAM
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(DS1307_NVRAM); // write the register address
  Wire.endTransmission();
  
  Wire.requestFrom(DS1307_ADDRESS,56); // ask for 56 bytes
  while (Wire.available()) {
      *ds1307TextPtr++ = Wire.read();
      bytes_read++;
      if (bytes_read > NVRAM_SIZE)
	break;
    }
  Wire.endTransmission();
  if (err)
    Serial.println("Error when reading to the DS1307 NVRAM");
  else {
    Serial.print(bytes_read);
    Serial.println(" characters read from the DS1307 NVRAM");
  }
  Serial.println(ds1307Text);
}

void loop() {
}
