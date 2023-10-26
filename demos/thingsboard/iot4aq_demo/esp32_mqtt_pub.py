# esp32_mqtt_pub.py: Reads temperature and humidity from the SHT30 temperature and humidity sensor.
# Uses temperature and humidity readings to calibrate the SGP30 air quality sensor.
# Reads the PM1.0, PM2.5 and PM10 dust concentration from the plantower device.
# Transmits all the readings to the ThingsBoard dash board for display.
# Copyright (c) U. Raich September 2023
# This program has been written for the Seminar on Air Quality and IoT-based Sensor Nov. 2023
# It is released under the MIT license

from umqtt.simple import MQTTClient
import machine
import network
import time,sys
from wifi_connect import connect
from pms5003 import PlanTower

# import the SHT3X class
from sht3x import SHT3X,SHT3XError
# import the SGP30 class
import sgp30

BROKER="192.168.0.36"
PORT="1885"
ACCESS_TOKEN="Bi2PyeEVu9u4fu3x8ECX"
TOPIC="v1/devices/me/telemetry"

SGP30_BASELINE=(0x951b, 0x9d1b)

# connect to the SHT30
try:
    sht30 = SHT3X()
except SHT3XError as exception:
    if exception.error_code == SHT3XError.BUS_ERROR:
        print("SHT30 module not found on the I2C bus, please connect it")
        sys.exit(-1)
    else:
         raise exception

# Get access to the SGP30
sgp30 = sgp30.SGP30()
print("SGP30 serial #", [hex(i) for i in sgp30.serial])

# Read the current temperature and humidity and pass the values to the
tempC, humi = sht30.getTempAndHumi(clockStretching=SHT3X.CLOCK_STRETCH,repeatability=SHT3X.REP_S_HIGH)

print("temperature: {:4.2f}°C and humidity: {:4.2f} transmitted to the SGP30".format(tempC,humi))
sgp30.set_iaq_baseline(SGP30_BASELINE[0], SGP30_BASELINE[1])
sgp30.set_iaq_relative_humidity(celsius=tempC, relative_humidity=humi)
meas_cycles = 0
# initialize the PMS5003
plantower = PlanTower()
plantower.clear_sums()

# Read 20 values from the SGP30 to settle the sensor
print("Dummy readings from the SGP30")
for i in range(30):
    print("eCO2 = %d ppm \t TVOC = %d ppb" % (sgp30.eCO2, sgp30.TVOC))
    time.sleep(1)
    
connect()
print("Connected, starting MQTTClient")
c = MQTTClient("umqtt_client", BROKER,port=PORT,user=ACCESS_TOKEN,password="")

try:
    c.connect()
except:
    print("Cannot connect, please check server IP and username and password")
    sys.exit()

print("Successfully connected to the ThingsBoard MQTT broker")
try:
    while True:
        # read temperature and humidity and publish the result
        tempC, humi = sht30.getTempAndHumi(clockStretching=SHT3X.CLOCK_STRETCH,repeatability=SHT3X.REP_S_HIGH)
        PAYLOAD="{" + "temperature: {:8.4f}, humidity: {:8.4f}".format(tempC,humi) + "}"
        print("PAYLOAD SHT30: ",PAYLOAD)
        c.publish(TOPIC,PAYLOAD)
        # read eCO2 and TVOC from the SGP30 and publish the result
        PAYLOAD = "{" + "eCO2:{:5d}, TVOC:{:5d}".format(sgp30.eCO2,sgp30.TVOC) + "}"
        print("PAYLOAD SGP30: ",PAYLOAD)
        c.publish(TOPIC,PAYLOAD)
        meas_cycles += 1
        if meas_cycles > 9:
            print("**** Baseline values: eCO2 = 0x{:04x}, TVOC = 0x{:04x}".format(
                sgp30.baseline_eCO2, sgp30.baseline_TVOC))
            meas_cycles = 0
        # get the dust densities from the PMS2005
        plantower.start()
        for i in range(5):
            plantower.read_raw()
            plantower.decode()
            plantower.sum()
        plantower.stop()
        PAYLOAD = "{" + "pm1_0:{:4.2f}, pm2_5:{:6.2f}, pm10:{:6.2f}".format(
            plantower.avr_results()["pm1_0_std_avr"],
            plantower.avr_results()["pm2_5_std_avr"],
            plantower.avr_results()["pm10_std_avr"],
            ) + "}"
        print("PAYLOAD of PlanTower PMS5003: ",PAYLOAD)
        c.publish(TOPIC,PAYLOAD)
            
except KeyboardInterrupt:
    c.disconnect()
    print("Stopping data transmission to the ThingsBoard MQTT broker")
