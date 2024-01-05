// blink.ino: Blinking the user LED on the ESP32
// The user LED is connected to GPIO 2
// We program this line to be output and the set a low and a high level for 500 ms each
// This makes the LED blink at a frequency of 1 Hz
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

#define LED_BUILTIN 2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for 500 ms
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
}
