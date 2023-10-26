# blink.py: blink the user LED
# demo program for the seminar on IoT based air quality sensors
# U. Raich

import sys
from utime import sleep_ms  # the utime module has delay functions
from machine import Pin     # this is the MicroPython GPIO driver
led = Pin(2,Pin.OUT)        # The user led is connected to GPIO 2
try:
    while True:
        led.value(not led.value()) # read the led state, invert it
                                   # and write it back
        sleep_ms(500)       # sleep for 500 ms
except KeyboardInterrupt:   # on <Ctrl> C: clear the led and exit
    led.off()
    sys.exit()
        
