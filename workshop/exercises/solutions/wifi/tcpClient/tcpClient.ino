/**
 * tcpClient.ino: Requests a TCP connect from a TCP server
 * Writes some text to the server and waits for a reponse
 * Terminates the connection by sending the message "bye"
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <Arduino.h>
#include <WiFi.h>
#include <string.h>

const char* ssid     = "your SSID";
const char* password = "your password";

void setup() {
  Serial.begin(115200);
  if (!Serial)
    delay(10);
  Serial.print("Trying to connect to ");
  Serial.println(ssid);

  if (strcmp(ssid,"your SSID") == 0) {
    Serial.println("Please add your correct SSID and password first");
    while (true)
      delay(100);
  }
  WiFi.begin(ssid,password); // connect to the network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected on ");
  Serial.println(WiFi.localIP());
}

void loop() {

  const uint16_t port = 5000;
  const char *medion_uli = "192.168.0.20";

  WiFiClient client;
  
  // Serial.print("Connected? ");
  // Serial.println(client.connected());
  if (!client.connected()) {
    Serial.print("Trying to connect to TCP server on ");
    Serial.println(medion_uli);
    if (!client.connect(medion_uli,port)) {
	      Serial.println("Connection to server on the PC failed");
	      delay(5000);
	      return;
    }
    else {
      Serial.print("Connected to server on \"");
      Serial.print(medion_uli);
      Serial.println("\"");
      // Serial.print("After successful connection: ");
      // Serial.println(client.connected());
      Serial.println("Trying to read from TCP");
    
      // wait for message from the server
      while (!client.available());
      // read the connection message from the server
      String msg = client.readStringUntil('\r');
      Serial.println(msg);
      Serial.setTimeout(100000); // set timeout to 10s
      while (true) {
        Serial.print("-> "); // write the prompt to the serial port
        // read some text from the serial line and send it to the server
        String sendmsgString = Serial.readStringUntil('\n');
        if ((sendmsgString == NULL) || (sendmsgString.substring(0,3) == String("bye"))){// if there is no input, give up
          // I use "substring" because the serial input may add <cr> and/or <lf>
          Serial.println("Stopping client");
          client.stop();
          // make sure the server has shut down
          delay(1000);
          return;
        }
        Serial.println(sendmsgString); 
        sendmsgString += "\n"; // add the ending <lf>
        const char *sendmsg = sendmsgString.c_str();
        client.write(sendmsg,strlen(sendmsg));
        // now wait for the server answer
        while (!client.available());
        // read the answer message from the server
        msg = client.readStringUntil('\r');
        Serial.print("Answer from server: ");
        Serial.println(msg);
      }
    }
  } 

}
