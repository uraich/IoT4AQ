/**
 * pms5003Raw.ino: reads a raw message from UART2 onto which the 
 * PlanTower PMS5003 must be connected
 * It synchronizes with the PMS5003 (waits for the magic word "BM"),
 * reads the full message and prints its contents as hex values
 * Copyright (c) U. Raich Jan 2024
 * This program is part of the IoT4AQ workshop held at the 
 * University Aliound Diop, Bambey Sénégal 
 * It is released under the MIT license
 */


#define RX 16
#define TX 17
#define PMS5003_MSG_LENGTH 32

void setup() {

  Serial.begin(115200);
  if (!Serial)
    delay(10);

  Serial.println("PMS5003 readout:");
  Serial2.begin(9600);

}

void loop() {
  uint8_t pms5003Msg[32];
  uint8_t *pms5003MsgPtr = &pms5003Msg[2];
  uint8_t firstChar='B';
  uint8_t secondChar='M';
  uint8_t inChar;
  int count=2;

  pms5003Msg[0] = firstChar;
  pms5003Msg[1] = secondChar;
  // synchronize by making sure that the first two characters are "BM"
  while (true) 
    if (Serial2.available()) {
      inChar = (uint8_t)Serial2.read();
      if (inChar == firstChar)
        break;
    }
 while (true) 
    if (Serial2.available()) {
      inChar = (uint8_t)Serial2.read();
      if (inChar == secondChar)
        break;
    }

  for (int i=2;i<sizeof(pms5003Msg);i++) {
    while (!Serial2.available()); // wait for the data to become available 
      *pms5003MsgPtr++ = (uint8_t) Serial2.read();
  }
  pms5003MsgPtr = pms5003Msg;
  for (int i=0;i<sizeof(pms5003Msg);i++) {
    Serial.print("0x");
    Serial.print(*pms5003MsgPtr++,HEX);
    Serial.print(" ");
  }
  Serial.println();
}
