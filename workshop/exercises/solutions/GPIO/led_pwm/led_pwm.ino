// led_pwm.ino: Modifies the LED light intensity using PWM
// The user LED is connected to GPIO 2
// 
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

#define LED_BUILTIN 2

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  int i;
  for (i=0; i<255;i++) { // increase the duty from zero to 255 which is the maximum
    analogWrite(LED_BUILTIN,i);
    delay(10);
  }
  for (i=255; i>0; i--) {
    analogWrite(LED_BUILTIN,i);
    delay(10);
  }    
      
}
