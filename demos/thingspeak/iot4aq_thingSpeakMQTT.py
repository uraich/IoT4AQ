# iot4aq_thinkSpeakMQTT.py
# Reads out the SHT30 temperature and humidity and sends the measurement
# to ThinkSpeak. This time the MQTT protocol is used for communication
# Temperature and humidity are used to calibrate the SGP30
# eCO2 and TVOC are read from the SGP30 and sent to ThingSpeak
# Finally the PlanTower PMS5003 is read out and the particle concentration
# sent to ThingSpeak
# copyright U. Raich
# This is a demo program for the Seminar on Air Quality and IoT based Air Sensors
# Released under the MIT license

from wifi_connect import connect
from umqtt.robust import MQTTClient
import time
# import the SHT3X class
from sht3x import SHT3X,SHT3XError

CLIENT_ID = b'AjgzFBIUPSA7HBgCGiEBIBQ'
USER_NAME = b'AjgzFBIUPSA7HBgCGiEBIBQ'
PASSWORD  = b'hTT2DrKidCzjCACvDqBn7XUm'

SERVER = b'mqtt3.thingspeak.com'
CHANNEL_ID = "2281416"
WRITE_API_KEY = "IYFTRVW8B7AU5JFG"
TIME_PUB_SEC = 15
