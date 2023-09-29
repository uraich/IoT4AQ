from umqtt.simple import MQTTClient
import network
import time,sys
from wifi_connect import *
# import the SHT3X class
from sht3x import SHT3X,SHT3XError

# Test reception e.g. with:
# mosquitto_sub -u iot4aq -P seminar2023 -t IoT4AQ

SERVER="192.168.0.20"
TOPIC="IoT4AQ"
# connect to the SHT30
try:
    sht30 = SHT3X()
except SHT3XError as exception:
    if exception.error_code == SHT3XError.BUS_ERROR:
        print("SHT30 module not found on the I2C bus, please connect it")
        sys.exit(-1)
    else:
         raise exception
     
connect()
print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", SERVER,user="iot4aq",password="seminar2023")

try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()
    
for _ in range(10):
    tempC, humi = sht30.getTempAndHumi(clockStretching=SHT3X.CLOCK_STRETCH,repeatability=SHT3X.REP_S_HIGH)
    PAYLOAD="Temperature: {:8.4f} degrees C, Humidity: {:8.4f}".format(tempC,humi)
    # print("PAYLOAD: ",PAYLOAD)
    c.publish(TOPIC,PAYLOAD)
    time.sleep(2)
c.disconnect()
