from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import *

# Test reception e.g. with:
# mosquitto_sub -t AIS2023 -u ais2023 -P johannesburg

SERVER="192.168.0.20"
TOPIC="AIS2023"
PAYLOAD=b"Welcome to the AIS2023 IoT tutorial"

connect()
print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", SERVER,user="ais2023",password="johannesburg")
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
