#!/bin/bash
# This shell scripts prepares the drivers needed for the IoT4AQ demos
# Demo program for the IoT presentation at the
# Seminar - Air Quality and IoT based Air sensors
# Nov 7-8, 2023
# Copyright (c) U. Raich Oct. 2023
# This program is released the MIT license

echo "Setting up the file system for IoT4AQ demos"
dirs="$(ampy ls)"
echo $dirs

#check if /lib already exists

if [[ $dirs == *"/lib"* ]]
then
    echo "/lib directory already exists"
else
    echo "Creating /lib directory"
    ampy mkdir /lib
fi
echo "Uploading the driver for the PlanTower PMS5003 dust sensor"
ampy put plantower/pms5003.py /lib/pms5003.py
echo "Uploading the driver for the SGP30 air quality sensor"
ampy put sgp30/sgp30.py /lib/sgp30.py
