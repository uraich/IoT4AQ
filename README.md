# IoT4AQ
## Slides and demonstration programs for the Seminar on Air Quality and IoT based Air Sensors
On 7. and 8. November 2023 an online [Seminar on Air Quality and IoT based Air Sensors](https://indico.cern.ch/event/1316999/page/30572-iot4aq-project) will be held. 
This repository contains slides of a tutorial on the Internet of Things in general and its application to air quality measurements in particular.  

The slides are available as LibreOffice odp documents as well as PDF files.

The MicroPython code for the all demonstrations shown during the presentation are collected in the demo folder. There you also find the drivers for the PlanTower dust sensor, the SGP air quality sensor and the SHT30 temperature and humidity sensor with small test programs making use of them:
1. led: Contains the emdedded systems _hello world_ program blink.py, which blinks the user LED on the ESP32 CPU board
2. in the plantower folder:
   1. pms5003.py is the driver for the PlanTower PMS5003 dust sensor
   2. plantowerDemo.py shows how to use it
3. in the sgp30 folder:
   1. i2cScan.py: scans the I2C bus and prints the addresses of all I2C modules found
   2. sgp30.py is the driver for the SGP30 air air quality sensor. This sensor returns measurements of eCO2 and TVOC
   3. sgp30_simpletest.py shows how to use it
4. in the sht30 folder:
   1. sht3x.py: the driver for the SHT30.
   2. sht3xTest.py: demonstrates the sht3x features
5. wifi: contains station.py demonstrating how to connect a station interface to the WiFi network
6. TCP: Shows how client-server communication works over TCP. In the PC folder there are server.py and client_withIP.py implementing client and serer on the PC. esp32TCP_server.py implements a TCP server on the ESP32
7. webserver: Implements a simple WEB server on the ESP32. First only a static page is provided, then a dynamic page, showing measurements in the WEB page through templates is demonstarted and finally a dynamic WEB page using server side events on the ESP32 and JavaScript on the browser is shown.
8. mosquitto: The programs in the mosquitto folder demonstrate how to communicate via the MQTT protocol. Again communication between the mosquitto broker and the subscriber and publisher are available in PC and ESP32 versions.
9. thingsboard: ThingsBoard is an IoT application that can be installed on a local PC or run in the cloud. It provides a dash board with widgets showing results from measurements, which have been communicated to it through a MQTT protocol (or HTTP). An example is available, collecting temperature and humidity data from a SHT30, eCO2 and TVOC data from a SGP30 and dust concentration from a PlanTower dust sensor and displaying the result on graphs. A second dash board controlling the user LED on the CPU board through ThnigsBoard widgets is provided.

The sht3x driver is already included in the MicroPython firmware I use and can therefore be accessed without further actions. The other drivers must be made availabe to the system by copying them into the /lib folder of the MicroPython file system.

# The IoT4AQ hands-on workshop
The slides and a demo program shown during the workshop are available here:
[Workshop on Air Quality and IoT based Air Sensors](https://github.com/uraich/IoT4AQ_B) 
