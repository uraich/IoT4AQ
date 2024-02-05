/* 
 * charPtr.ino: printing the character codes of "Hello World!"
 * 
 * Copyright (c) U. Raich) Feb. 2024
 * This program is part ot the IoT4AQ workshop held in March 2024 at
 * the University Alioune Diop, Bambey, Sénégal
 * It is released under the MIT license
 */

void setup () {
  char *hello = "Hello World!";
  uint8_t *helloPtr = (uint8_t *) hello;
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  while (*helloPtr != '\0') { // go through the C string until you find
                              // the terminating zero

    Serial.print("0x");
    Serial.print(*helloPtr++,HEX);
    Serial.print(", ");
  }
  Serial.print("0x");
  Serial.print(*helloPtr);
}
void loop() {}
