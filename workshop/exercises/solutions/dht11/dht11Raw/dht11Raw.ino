// dht11Raw.ino: Reads the raw data from the DHT11 data line
// The program starts a measurement, the re-programs the DHT11 data line
// from output to input and reads the data line every 4 us. The status
// of the data line is saved into an array of 32 elements of 32 bits each.
// This makes the LED blink the SOS morse code
// The program is part of the workshop on IoT4AQ at Alioune Diop University, Bambey, Sénégal

#define DATA_LINE 16

void setup() {
  unsigned int dht11RawData[32];
  unsigned int *buf;
  int i,j;
  // initialize the serial line
  Serial.begin(115200);
  // initialize the DHT11 data line to output first
  // this allows to start the measurement
  pinMode(DATA_LINE, OUTPUT);
  // issue the start command
  digitalWrite(DATA_LINE,HIGH);
  delay(250);                   // keep it high for 250 ms
  digitalWrite(DATA_LINE,LOW);  // this starts the measurement
  delay(18);
  // bring it back to high start and switch to reading
  digitalWrite(DATA_LINE,HIGH);
  delayMicroseconds(10);
  pinMode(DATA_LINE, INPUT);    // switch the data line to input and start reading
  
  // read for 32x32 us and save the result in an integer array
  // point to the beginning of the result array
  buf = dht11RawData;
  for (i=0;i<32;i++) {
    *buf = 0;                   // clear the data word
    for (j=0;j<32;j++) {  
      *buf = *buf << 1 | digitalRead(DATA_LINE); // shift the bit into the data word
      delayMicroseconds(4);                               // do this every 
    }
    buf++;
  }
  // Finally we simply print the results for further treatment
  for (i=0;i<32;i++)
    Serial.println(dht11RawData[i],HEX);
}

void loop() {} // since we do the work only once, the loop part stays empty
