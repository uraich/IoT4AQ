/* arithmetic_int.ino: Demonstrates variable declaration and basic arithmetic
 *
 * Copyright (c) U. Raich, Jan. 2024
 * This program is part of the IoT4AQ workshop held at
 * the University Alioune Diop, Bamabey, Sénégal
 * It is released under the MIT license
 */

void setup() {
  Serial.begin(115200);
  if (!Serial)
    delay(10);
}

void loop() {
  int a,b,c;
  a = 7;
  b = 5;
  // here fore the addition
  c = a + b;
  Serial.print("The result of addition:        ");
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(c);

  // here for subtraction
  c = a - b; // c is overwritten
  Serial.print("The result of subtraction:     ");
  Serial.print(a);
  Serial.print(" - ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(c);

  // here for multiplication
  c = a * b;
  Serial.print("The result of multiplication:  ");
  Serial.print(a);
  Serial.print(" * ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(c);

  // here for division
  c = a / b;
  Serial.print("The result of division:        ");
  Serial.print(a);
  Serial.print(" / ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(c);
  Serial.println();
  delay(1000);
}
