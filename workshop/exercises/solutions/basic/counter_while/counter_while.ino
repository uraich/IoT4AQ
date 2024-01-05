// counter_while.ino: Implements an up and down counter using
// while loops
// The current value is printed on the serial monitor
// This program is part of the IoT4AQ workshop at
// Alioune Diop University, Bambey, Sénégal

void setup() {
  Serial.begin(115200);
}

void loop() {
  int counter;
  counter = 0; // initilize the counter
  while (counter < 41) {
    Serial.println(counter);
    counter++;
    delay(100); // put a delay such that we can see the printed value 
  }
  counter--;
  while (counter > 1) {
    counter--;
    Serial.println(counter);
    delay(100);
  }

}
