// plotter.ino: A simple program plotting trigonometric functions
// and demonstrating the plotting facility of the Arduino SDK
// The 100 values of the sin and cos functions are calculated over
// a full period. We calculate a new value 
#include <math.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Calculate sin and cos values every 10 ms
  int i;
  double s,c,x;
  double increment = 2.0*M_PI/40.0;
  Serial.print("increment: ");
  Serial.println(increment);
  while (true) {
    for (i=0;i<40;i++) {
      x = i * increment;
      s = sin(x);
      c = cos(x);
      Serial.print(x);
      Serial.print(" ");
      Serial.print(s);
      Serial.print(" ");
      Serial.println(c);
      delay(20);
    }
  }
}
