#!/usr/bin/python3
import socket

def get_ip():
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    try:
        # doesn't even have to be reachable
        s.connect(('192.255.255.255', 1))
        IP = s.getsockname()[0]
    except Exception:
        IP = '127.0.0.1'
    finally:
        s.close()
    return IP

def server_program():
    # get the hostname
    host = socket.gethostname()
    port = 5000  # initiate port no above 1024

    server_socket = socket.socket()  # get instance
    # look closely. The bind() function takes tuple as argument
    server_socket.bind(('', port))  # bind host address and port together

    print("Server running on " + host + " with IP: " + get_ip())
    print("Listening to any machine on port ",port)
    
    # configure to how many clients the server can listen simultaneously
    server_socket.listen(1)
    conn, address = server_socket.accept()  # accept new connection
    print("Connection from: " + str(address))
    conn.send(("From server: Connected to " + get_ip()).encode()) # convert string to byte array
    
    while True:
        # receive data stream. it won't accept data packet greater than 1024 bytes
        data = conn.recv(1024).decode()     # convert byte array to string
        if not data:
            # if data is not received break
            break
        print("from connected user: " + data)
        data = input(' -> ')
        conn.send(data.encode())  # send data to the client

    conn.close()  # close the connection
    
if __name__ == '__main__':
    server_program()
