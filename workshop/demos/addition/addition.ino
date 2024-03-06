/* 
 * addition.ino: A very basic Arduino program adding 2 numbers and printing
 * the result 
 * 
 * Copyright (c) U. Raich) Feb. 2024
 * This program is part ot the IoT4AQ workshop held in March 2024 at
 * the University Alioune Diop, Bambey, Sénégal
 * It is released under the MIT license
 */

void setup() {
  Serial.begin(115200); // start the serial line at 115200 baud
  if (!Serial)
    delay(10);
}

void loop() {  
  int a,b,c;
  a=7;
  b=5;
  c=a+b;
  // print the result on the serial monitor
  Serial.print("The result of the addition: "); // This is a text string. With print, the next character is printed on the same line
  Serial.print(a);                              // Prints the contents (value) of variable a
  Serial.print(" + ");                          // Again a text string
  Serial.print(b);                              // the value of b
  Serial.print(" = ");                          // again text
  Serial.println(c);                            // and finally the result of the addition which was saved in variable c
  delay(10000);                                 // wait for 10s (10000 ms) before we do the calculation again
                                                // remember that the code in loop() is repeated
}
