/* 
 * number2string.ino: Converting integers and floats to strings
 * This may be needed for the LCD display
 * 
 * Copyright (c) U. Raich) Feb. 2024
 * This program is part ot the IoT4AQ workshop held in March 2024 at
 * the University Alioune Diop, Bambey, Sénégal
 * It is released under the MIT license
 */

void setup() {
  Serial.begin(115200); // open the serial port at a speed of 115200 baud (bits per second)
  while (!Serial)       // wait until the serial line is ready
    delay(10);
}

void loop() {
  float a = 123.45;
  int b = 345;
  char floatBuf[10];
  char decIntBuf[10];
  char hexIntBuf[10];

  itoa(b,decIntBuf,10);
  itoa(b,hexIntBuf,16);
  dtostrf(a,3,2,floatBuf);

  Serial.print("Converted int to decimal: ");
  Serial.println(decIntBuf);

  Serial.print("Converted int to hex: 0x");
  Serial.println(hexIntBuf); 

  Serial.print("Converted float: ");
  Serial.println(floatBuf);

  Serial.println();
  delay(10000);
}
