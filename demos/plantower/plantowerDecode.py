# PlantowerDecode.py: Initializes UART 2 on Rx: GPIO 22 and Tx: GPIO 21
# Reads incoming messages from the sensor and decodes them
# Calculates the checksum
# Copyright (c) U.Raich, Sep 2022
# This program is part of a course on the Internet of Things at the
# University of Cape Coast, Ghana
# It is released under the MIT License

import machine,sys

PMS5003_MSG_LENGTH = 32
PMS5003_MAGIC    = b'\x42\x4d'
MAGIC_POS        =  0
FRAME_LENGTH_POS =  2
PM1_0_STD_POS    =  4
PM2_5_STD_POS    =  6
PM10_STD_POS     =  8

PM1_0_ATM_POS    = 10
PM2_5_ATM_POS    = 12
PM10_ATM_POS     = 14

BEYOND_0_3_POS   = 16
BEYOND_0_5_POS   = 18
BEYOND_1_0_POS   = 20
BEYOND_2_5_POS   = 22
BEYOND_5_0_POS   = 24
BEYOND_10_POS    = 26   
RESERVED         = 28
CHKSUM_POS       = 30

def calculateChecksum(message):
    calculated_chksum = 0
    for i in range(PMS5003_MSG_LENGTH-2):
        calculated_chksum += message[i]
    return calculated_chksum

def checksumInMessage(message):
    return message[CHKSUM_POS] << 8 | message[CHKSUM_POS+1]
            
def decode(message):
    magic = message[MAGIC_POS:MAGIC_POS+2]
    print(type(magic))
    print("Start characters: " + magic.decode())
    if magic != PMS5003_MAGIC :
        print("Not a valid PlanTower message")
        sys.exit()
    print("Found a valid PlanTower message")
        
    frame_length = message[FRAME_LENGTH_POS] << 8 |  message[FRAME_LENGTH_POS+1]
    print('frame length: {:04d}'.format(frame_length))
    if frame_length != PMS5003_MSG_LENGTH - 4:
        print('Message with wrong frame length from PlanTower sensor')
        sys.exit()
    print("Frame length: {:d} is correct".format(frame_length))
    print("Calculated checksum: 0x{:04x}, checksum in message: 0x{:04x}".format(
        calculateChecksum(message),checksumInMessage(message)))
    if calculateChecksum(message) != checksumInMessage(message) :
        print("Checksum error!")
        sys.exit()

    pm1_0_std = message[PM1_0_STD_POS] << 8 | message[PM1_0_STD_POS+1]
    pm2_5_std = message[PM2_5_STD_POS] << 8 | message[PM2_5_STD_POS+1]
    pm10_std  = message[PM10_STD_POS]  << 8 | message[PM10_STD_POS+1]
    
    pm1_0_atm = message[PM1_0_ATM_POS] << 8 | message[PM1_0_ATM_POS+1]
    pm2_5_atm = message[PM2_5_ATM_POS] << 8 | message[PM2_5_ATM_POS+1]
    pm10_atm  = message[PM10_ATM_POS]  << 8 | message[PM10_ATM_POS+1]
    
    beyond_0_3 = message[BEYOND_0_3_POS] << 8 | message[BEYOND_0_3_POS+1]
    beyond_0_5 = message[BEYOND_0_5_POS] << 8 | message[BEYOND_0_5_POS+1]
    beyond_1_0 = message[BEYOND_1_0_POS] << 8 | message[BEYOND_1_0_POS+1]
    beyond_2_5 = message[BEYOND_2_5_POS] << 8 | message[BEYOND_2_5_POS+1]
    beyond_5_0 = message[BEYOND_5_0_POS] << 8 | message[BEYOND_5_0_POS+1]
    beyond_10  = message[BEYOND_10_POS]  << 8 | message[BEYOND_10_POS+1]

uart2 = machine.UART(2,baudrate=9600,rx=17,tx=16,timeout=10000)
rawline = uart2.read(PMS5003_MSG_LENGTH)
print(rawline)
decode(rawline)                     
