from machine import Pin
from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import connect
import os
osVersion=os.uname()

# Test publication e.g. with:
# mosquitto_pub -u iot4aq -P seminar2023 -t IoT4AQ -m "LED on"

SERVER="192.168.0.20"
TOPIC="IoT4AQ"

def cmdCallback(topic,payload):
    print("topic: {:s}, payload: {:s}".format(topic.decode(),payload.decode()))
    if payload == b"LED on":
        userLed.on()
    elif payload == b"LED off":
        userLed.off()
        
# if there is 'spiram' in the machine name then we are on the T7 V1.4 or V1.5
if osVersion.machine.find('spiram') == -1:
    _LED_PIN = 2
else:
    print("Running on an ESP32 WROVER")
    _LED_PIN = 19

userLed = Pin(_LED_PIN,Pin.OUT)
# connect to WiFi
connect()

print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", SERVER,user="iot4aq",password="seminar2023")
try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()

c.set_callback(cmdCallback)
c.subscribe(TOPIC)

print("Waiting for messages on topic 'IoT4AQ' from MQTT broker")
while True:
    c.wait_msg()
