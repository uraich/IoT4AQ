/**
 * scanWiFi.ino: Scans the WiFi network and prints information
 * on all SSIDs found
 *
 * Copyright (c) U. Raich, January 2024
 * This program is part of the IoT4AQ workshop at the 
 * university Alioune Diop, Bambey, Sénégal, 2024
 * It is released under the MIT license
 */

#include <WiFi.h>
#include <WiFiScan.h>

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10);

  // put WiFi to station mode
  WiFi.mode(WIFI_STA);
  // disconnect it it was connected
  WiFi.disconnect();
  delay(100);
}

void loop() {
  // SSID is the Service Set Identifier (name of your network)
  // BSSID is the basic Service Set Identifier. It is basically the MAC address of the wireless router
  // RSSI is the received signal strength indicator

  int noOfNetworks = WiFi.scanNetworks(false,true); // show hidden networks
  Serial.print(noOfNetworks);
  Serial.println(" networks found");
  Serial.println("network number   SSID          encryption       RSSI         BSSID           channel");
  for (int i=0;i<noOfNetworks;i++)  {
    Serial.print("\t");
    Serial.print(i);
    Serial.print("\t");
    if (WiFi.SSID(i) == String(""))
      Serial.print("hidden\t");
    else
      Serial.print(WiFi.SSID(i));
    Serial.print("\t");
    switch (WiFi.encryptionType(i))
    {
      case WIFI_AUTH_OPEN:
	      Serial.print("open");
	      break;
      case WIFI_AUTH_WEP:
	      Serial.print("WEP\t");
	      break;
      case WIFI_AUTH_WPA_PSK:
	      Serial.print("WPA\t");
	      break;
      case WIFI_AUTH_WPA2_PSK:
	      Serial.print("WPA2\t");
	      break;
      case WIFI_AUTH_WPA_WPA2_PSK:
	      Serial.print("WPA+WPA2");
	      break;
      case WIFI_AUTH_WPA2_ENTERPRISE:
	      Serial.print("WPA2-EAP");
	      break;
      case WIFI_AUTH_WPA3_PSK:
	      Serial.print("WPA3\t");
	      break;
      case WIFI_AUTH_WPA2_WPA3_PSK:
	      Serial.print("WPA2+WPA3");
	      break;
      case WIFI_AUTH_WAPI_PSK:
	      Serial.print("WAPI\t");
	      break;
      default:
	      Serial.print("unknown");
    }
    Serial.print("\t");
    Serial.print(WiFi.RSSI(i));
    Serial.print("\t");
    Serial.print(WiFi.BSSIDstr(i));
    Serial.print("\t");
    Serial.println(WiFi.channel(i));
  }
  Serial.println();
  delay(5000);
}
