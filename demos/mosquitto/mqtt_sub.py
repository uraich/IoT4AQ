from machine import Pin
from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import connect

# Test publication e.g. with:
# mosquitto_pub -u ais2023 -P johannesburg -t AIS2023 -m "LED on"

SERVER="192.168.0.20"
TOPIC="AIS2023"

def cmdCallback(topic,payload):
    print("topic: {:s}, payload: {:s}".format(topic.decode(),payload.decode()))
    if payload == b"LED on":
        userLed.on()
    elif payload == b"LED off":
        userLed.off()    

userLed = Pin(19,Pin.OUT)
# connect to WiFi
connect()

print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", SERVER,user="ais2023",password="johannesburg")
try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()

c.set_callback(cmdCallback)
c.subscribe(TOPIC)

print("Waiting for messages on topic 'AIS2023' from MQTT broker")
while True:
    c.wait_msg()
