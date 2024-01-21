/*
  functions.ino: Demonstrates the use of functions
  Copyright (c) U. Raich, Jan 2024
  This program is part of the IoT4AQ workshop at the
  University Alioune Diop, Bambey, Sénégal
  It is released under the MIT license
*/

// Define the function to calulate a straight line
// The mathematical equation is y = mx + b, where m is the slope
// and b is the y axis intercept

float line(float m, float b, float x) {
  return (m*x + b);
}
void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);
}

void loop() {
  float slope = 2.0;          // the slope
  float y_intersect = 1.0;    // the intersect on the y-axis
  float x;
  for (int i=0; i<50; i++) { // a for loop over 100 x values
    x = 0.1*i;                // x is now in the range 0..10.0
    Serial.print(0);          // This fixes the lower bound of the plotting range
    Serial.print(" ");
    Serial.print(11);         // and this one the upper bound
    Serial.print(" ");
    Serial.print("y = ");
    Serial.println(line(slope, y_intersect, x)); 
    delay(10);                // calculate a new point every 10 ms
  }
  delay(10000);
}
