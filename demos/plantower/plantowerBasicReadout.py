# PlantowerBasicReadout.py: Initializes UART 2 on Rx: GPIO 17 and Tx: GPIO 16
# Reads incoming messages from the sensor and prints them
# Copyright (c) U.Raich, Sep 2022
# This program is part of a course on the Internet of Things at the
# University of Cape Coast, Ghana
# It is released under the MIT License

import machine

PMS5003_MSG_LENGTH = 32
uart2 = machine.UART(2,baudrate=9600,rx=17,tx=16,timeout=10000)
while True:
    rawline = uart2.read(PMS5003_MSG_LENGTH)
    print(rawline)
                     
