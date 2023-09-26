# IoT4AQ
## Slides and demonstration programs for the Seminar on Air Quality and IoT based Air Sensors
On 6. and 7. November 2023 an online [Seminar on Air Quality and IoT based Air Sensors](https://indico.cern.ch/event/1316999/page/30572-iot4aq-project) will be held. 
This repository contains slides of a tutorial on the Internet of Things in general and its application to air quality measurements in particular.  

The slides are available as LibreOffice odp documents as well as PDF files.

The MicroPython code for the demonstrations are found in the demo folder. There are drivers for the following sensors with small test programs making use of them:
1. in the plantower folder:
   1. pms5003.py is the driver for the PlanTower PMS5003 dust sensor
   2. plantowerDemo.py shows how to use it
2. in the sgp30 folder:
   1. i2cScan.py: scans the I2C bus and prints the addresses of all I2C modules found
   2. sgp30.py is the driver for the SGP30 air air quality sensor. This sensor returns measurements of eCO2 and TVOC
   3. sgp30_simpletest.py shows how to use it
3. in the sht30 folder:
   1. sht3x.py: the driver for the SHT30.
   2. sht3xTest.py: demonstrates the sht3x features

The sht3x driver is already included in the MicroPython firmware I use and can therefore accessed without further actions. The other drivers must be made availabe to the system by copying them into the /lib folder of the MicroPython file system.
