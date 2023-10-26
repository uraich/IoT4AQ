# The simplest possible WEB server printing "Hello World!"
# Program written for the IoT course at the University of Cape Coast
# This first version does not use picoweb but accesses the socket interface
# directly
# copyright (c) U. Raich April 2020
# This program is released under GPL

import time,sys
import network
import socket
import wifi_connect
import uerrno

print ("Connecting to the network")
wifi_connect.connect()
ipaddr=wifi_connect.getIPAddress()

html = """ <!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
</head>
<body>
<title>Hello World </title>
<h1>The Hello World! HTML page</h1>
<p>This is the Hello World html page Version 1, served by a WEB server communicating through sockets directly.<br>
  The html code is embedded in the server itself. There is no separate HTML file. <br>
  The program was written for
  the <b>Seminar - Air Quality and IoT-based Air Sensors  </b><br>
  Copyright (c) U. Raich, Oct 2023, <br>released under the MIT License
  
</p>

</body>
</html> 
"""

# listen to a socket on port 80 

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

try:
    s.bind(('',80))
except OSError as exception:
    if exception.args[0] == uerrno.EADDRINUSE:
        print("Socket is already bound, please reset the machine")
        sys.exit()

            
s.listen(5)
print("Starting the Hello World WEB server on IP address ",ipaddr,"port 80")

while True:
  conn,addr=s.accept()
  print("GOT a connection from %s" % str(addr))
  request=conn.recv(1024)
  print("Content %s" % str(request))
  response=html
  conn.send(response)
  conn.close() 
