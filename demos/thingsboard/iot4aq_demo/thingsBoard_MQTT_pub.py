#!/usr/bin/python3
# 
# thingyBoard_MQTT_pub.py : Publishes a few messages to the ThingsBoard broker

from paho.mqtt import client as mqtt_client
import random,time

print("Demonstration how to publish a message on the mosquitto broker")

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            client.connected_flag=True #set flag
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
            
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.loop_start()
    print("Trying to connect")
    client.connect(broker, port)
    
    while not client.connected_flag: #wait in loop
        print("In wait loop")
        time.sleep(1)
    return client

def publish(client,temp,humi,led):
    msg = '{' + 'temperature:{:4.2f}, humidity:{:4.2f}, led:{:d}'.format(temp,humi,led) + '}'
    result = client.publish(topic, msg)
    # result: [0, 1]
    status = result[0]
    if status == 0:
        print('{' + 'temperature:{:4.2f}, humidity:{:4.2f}, led:{:d}'.format(temp,humi,led) + '}')
    else:
        print(f"Failed to send message to topic {topic}")
         
random.seed(42)
random.randrange(0,10)

mqtt_client.Client.connected_flag=False#create flag in class
broker = 'localhost'
port = 1885
topic = "v1/devices/me/telemetry"
client_id = f'python-mqtt-{random.randint(0, 1000)}'
print("Client id: ",client_id)

username = 'Bi2PyeEVu9u4fu3x8ECX'   # user name == Access token
password = ''
client = connect_mqtt()
led = True
while True:
    temp=15 + 5*random.random()
    humi=55 + 10*random.random()
    if led:
        publish(client,temp,humi,1)
    else:
        publish(client,temp,humi,0)
    led = not led
    time.sleep(5)

client.loop_stop()                  #Stop loop 
client.disconnect()                 # disconnect
