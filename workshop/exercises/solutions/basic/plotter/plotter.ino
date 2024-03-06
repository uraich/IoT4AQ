// plotter.ino: A simple program plotting trigonometric functions
// and demonstrating the plotting facility of the Arduino SDK
// The 40 values of the sin and cos functions are calculated over
// a full period. We calculate a new value every 20 ms
#include <math.h>

#define NO_OF_VALUES 40

void setup() {
  Serial.begin(115200);
}

void loop() {
  // Calculate sin and cos values every 20 ms
  int i;
  double s,c,x;
  double increment = 2.0*M_PI/(float)NO_OF_VALUES;
  Serial.print("increment: ");
  Serial.println(increment);
  while (true) {
    for (i=0;i<NO_OF_VALUES;i++) {
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
