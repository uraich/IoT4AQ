// The hello world program for the ESP32 on the Arduino SDK
// This program is part of the IoT4AQ hand-on workshop at
// Alioune Diop University Bambay, Sénégal, 2024

void setup() {
  // Initilize the serial port for a baudrate of 115200
  Serial.begin(115200);
}

void loop() {
  // print "Hello World!" every second
  // you will see the result on the serial monitor
  // make sure that its baud rate corresponds to the one used in setup()
  Serial.println("Hello World!");
  delay(1000);
}
