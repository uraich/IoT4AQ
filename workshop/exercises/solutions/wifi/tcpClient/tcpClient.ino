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

#include <WiFi.h>

const char* ssid     = "WLAN18074253";
const char* password = "Q4k6V35sFauw";
