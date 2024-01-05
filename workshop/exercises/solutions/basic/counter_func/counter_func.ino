// counter_func.ino: An up/down counter implemented as 2 functions
// The maximum value is passed as an argument
void up_counter(int max) {
  for (int counter=0; counter<max; counter++) {
    Serial.println(counter);
    delay(100);
  }
  return;
  }

void down_counter(int max) {
    for (int counter=max; counter > 0; counter-- ) {
      Serial.println(counter);
      delay(100);
    }
    return;
  }

void setup() {
  Serial.begin(115200);

}

void loop() {
  up_counter(40);
  down_counter(40);
}
