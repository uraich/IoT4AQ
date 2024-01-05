#include <Wire.h>

// Set I2C bus to use: Wire, Wire1, etc.
#define WIRE Wire

void setup() {
  char txt_buf[3]; // 2 hex characters + the ending 0
  byte error,address;
  WIRE.begin();

  Serial.begin(115200);
  while (!Serial)
     delay(10);
  Serial.print("\nI2C Scanner on SCL: ");
  Serial.print(SCL);
  Serial.print(" and SDA: ");
  Serial.println(SDA);
  Serial.println("Copyright (c) U. Raich");
  Serial.println("Program written for the IoT4AQ workshop at the");
  Serial.println("University Alioune Diop, Bambey, Sénégal 2024");
  Serial.println("This program is released under the MIT license\n");
  Serial.println("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f");

  for (int i=0; i<8; i++) {
    sprintf(txt_buf,"%02x",i*16);
    Serial.print(txt_buf);
    Serial.print(": ");
    for (int j=0; j<16; j++) {
      address = i*16 + j;
      WIRE.beginTransmission(address);
      error = WIRE.endTransmission();
      if (!error) {
        sprintf(txt_buf,"%02x",address);
        Serial.print(txt_buf);
        Serial.print(" ");
      }
      else 
        Serial.print("-- ");
    }
    Serial.println("");

  }

}


void loop() {}
