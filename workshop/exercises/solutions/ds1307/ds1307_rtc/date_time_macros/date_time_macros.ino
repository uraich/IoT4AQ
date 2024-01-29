// try to print the __DATE__ and __TIME__ macros

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  Serial.print("__TIME__: ");
  Serial.print(__TIME__);
  Serial.print(", __DATE__ :");
  Serial.println(__DATE__);
}

  void loop() {}
