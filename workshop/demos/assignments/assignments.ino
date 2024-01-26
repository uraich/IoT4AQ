void setup() {
  Serial.begin(115200); // open the serial port at a speed of 115200 baud (bits per second)
  while (!Serial)       // wait until the serial line is ready
    delay(10);
}

void loop() {
  int a,b,c; // the variables a .. c are of type integer "//" designates a comment and is not executed
             // the ";" ends the instruction and is needed at each line of code
  a = 7;
  b = 5;
  c = a+b;
  Serial.print("The result of the addition: "); // when issuing "print" the net character will be printed on the same line
  Serial.print(a);                             
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(c);      // when issuing "println" the next character will 
                          // be printed at the beginning of the next line
  delay(10000);           // wait for 10 s before repeating the calculation
}