/* parabola.ino: A simple program plotting a parabola
 * and demonstrating the plotting facility of the Arduino SDK
 * The 50 values of the parabola equation are calculated over a range
 * of -2 .. 2. We calculate a new value every 10 ms and then 10 s
 * before repeating the calculations
 *
 * Copyright (c) U. Raich, Jan. 2024
 * This program is part of the IoT4AQ workshop held at
 * the University Alioune Diop, Bamabey, Sénégal
 * It is released under the MIT license
 */

// the equation of a parabola is y = a(x-h)*(x-h) + k
// where (h,k) denotes the vertex

float parabola(float a,float h,float k,float x) {
  return(a*(x-h)*(x-h) + k);
}

void setup() {
  Serial.begin(115200);
}

void loop() {
  float a = 1.5;
  float h = 2.0;
  float k = 1.0;
  float x;
  for (int i=0;i<50;i++) {
    x = (4.0 / 50.0)*i -2.0;
    //Serial.print("parabola: ");
    Serial.println(parabola(a,h,k,x));
    delay(10);
  } 
  delay(10000);
}
