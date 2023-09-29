from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import *

# Test reception e.g. with:
# mosquitto_sub -u iot4aq -P seminar2023 -t IoT4AQ

SERVER="192.168.0.20"
TOPIC="IoT4AQ"
PAYLOAD=b"Welcome to the IoT4AQ tutorial"

connect()
print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", SERVER,user="iot4aq",password="seminar2023")
# c = MQTTClient("umqtt_client", SERVER)
try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()
    
for _ in range(10):
    c.publish(TOPIC,PAYLOAD)
    time.sleep(1)
c.disconnect()
