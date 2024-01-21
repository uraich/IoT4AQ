// pb_basic.ino: demonstrates how to use a GPIO line to determine the state
// of a digital signal e.g. the state of a push button
// In this program the switch state is read every 100 ms and its state is
// printed to the serial monitor 
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

# define PUSH_BUTTON 22 // This is the GPIO line the pushbutton on the
                        // WeMos D1 mini shield uses
                        // On the ESP32 DevKit-C you may use the boot button
                        // which is connected to GPIO 0
void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);          // wait for the serial port to become available
  // initialize digital pin for the PUSHBUTTON as an input.
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
}

void loop() {
  for (int i=0; i<100; i++) {
    Serial.print(digitalRead(PUSH_BUTTON)); // read and print the button state
    delay(100);                      // every 100 ms
  }
  Serial.println("");
}
