// pb_change.ino: demonstrates how to use a GPIO line to determine the state
// of a digital signal e.g. the state of a push button
// In this version the state of the push button is only indicated if it
// changed.
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

# define PUSH_BUTTON 22 // This is the GPIO line the pushbutton on the
                        // WeMos D1 mini shield uses
                        // On the ESP32 DevKit-C you may use the boot button
                        // which is connected to GPIO 0
bool new_state,old_state;

void printState(bool state) {
  if (state)
    Serial.println("Button released");
  else
    Serial.println("Button pressed");    
}

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);          // wait for the serial port to become available
  // initialize digital pin for the PUSHBUTTON as an input.
  pinMode(PUSH_BUTTON, INPUT_PULLUP);
  old_state = digitalRead(PUSH_BUTTON);
  printState(old_state);    // print the state when the program is started
}

void loop() {       
  new_state = digitalRead(PUSH_BUTTON); // read the current state
  if (new_state != old_state) {         // indicate the state only if it has changed
    old_state = new_state;
    printState(new_state);
  }
  delay(100);
}
 
