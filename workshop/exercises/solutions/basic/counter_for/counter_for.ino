// counter_for.ino: Implements an up/down counter using for loops
// This program is part of the IoT4AQ workshop at the
// University Alioune Diop, Bambey, Sénégal

void setup() {
  Serial.begin(115200);
  while (!Serial):
    delay(10);
}

void loop() {
  int counter;
  for (counter=0; counter<40; counter++) {
    Serial.println(counter);
    delay(100);
  }
  for (counter=40; counter>0; counter--) {
    Serial.println(counter);
    delay(100);
  }

}
