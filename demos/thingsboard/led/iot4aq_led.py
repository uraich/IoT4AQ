from machine import Pin
from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import connect
import os
import json
osVersion=os.uname()

# Test publication e.g. with:

BROKER="192.168.0.36"
PORT="1885"
ACCESS_TOKEN="Px3DCnkuK6g86MNPbgwc"
TOPIC="v1/devices/me/telemetry"
RPC_REQUEST="v1/devices/me/rpc/request/+"
ATTR="v1/devices/me/attributes"

def cmdCallback(topic,payload):
    topic_string = topic.decode()
    payload_string = payload.decode()
    print("topic: {:s}, payload: {:s}".format(topic_string, payload_string))
    dict = json.loads(payload)
    # The setValue method
    if dict["method"] == "setValue":
        if dict["params"]:
            userLed.on()
        else:
            userLed.off()
        ledState = userLed.value()
        if ledState:
            ledResponse = "true"
        else:
            ledResponse = "false"
        indicator_topic = "{value:" + ledResponse + "}"
        print("indicator topic: {}".format(indicator_topic))
        c.publish(TOPIC,indicator_topic)
    # The checkStatus method
    elif dict["method"] == "checkStatus":
        
        response_topic_string = topic_string.replace("request","response")
        print("response topic: " + response_topic_string)
        ledState = userLed.value()
        if ledState:
            ledResponse = "true"
        else:
            ledResponse = "false"
        led_resonse_payload = "{value:" + ledResponse + "}" 
        print("Response payload: {}".format(response_payload_string))
        # convert to null terminated C type string
        c.publish(response_topic_string.encode(),response_payload_string.encode())
              
            
# if there is 'spiram' in the machine name then we are on the T7 V1.4 or V1.5
if osVersion.machine.find('spiram') == -1:
    _LED_PIN = 2
else:
    print("Running on an ESP32 WROVER")
    _LED_PIN = 19

userLed = Pin(_LED_PIN, Pin.OUT)
# connect to WiFi
connect()

print("Connected, starting MQTTClient")
c =  MQTTClient("umqtt_client", BROKER,port=PORT,user=ACCESS_TOKEN,password="")
try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()

print("Successfully connected to ThingsBoard broker")
c.set_callback(cmdCallback)
c.subscribe(RPC_REQUEST)

print("Waiting for messages on topic 'ThingsBoard' from MQTT broker")
while True:
    c.wait_msg()
