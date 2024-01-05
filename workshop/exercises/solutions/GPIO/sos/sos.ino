// sos.ino Blinks the SOS morse code on the user LED of the ESP32
// The user LED is connected to GPIO 2
// We program this line to be output and the set a low and a high level for 200 ms for the "S" code
// and 700 ms for the "O" code.
// This makes the LED blink the SOS morse code
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

#define LED_BUILTIN 2
#define PAUSE       200 // interval between two blinks
#define SHORT       200 // the short signal for the "S"
#define LONG        700 // the long signal for the "O"

void on_off(int duration) {
  // switches 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(duration);
  digitalWrite(LED_BUILTIN, LOW);
  delay(PAUSE);
}

void s() {
  for (int i=0; i<3; i++)
    on_off(SHORT);
}

void o() {
  for (int i=0; i<3; i++)
    on_off(LONG);
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // send an SOS
  s(); o(); s();
  // wait for a second before sending the next one
  delay(1000);
}
