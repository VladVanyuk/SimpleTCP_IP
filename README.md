# Simple TCP_IP calculator
TCP/IP server and client on localhost with port 8080 in C language.
Server - Client Calculator using socket programming.

Compile the Server.c and Client.c files.
gcc server.c -o server
gcc client.c -o client

IP and PORT configurations are in config.h file.
config.h is required to run client file properly.

Run the server file as
./server

Run in another terminal client file:
./client

The Client will be prompt to enter the two numbers and run a command based on Choices:
1. Addition 
2. Subtraction 
3. Division 
4. Multiplication 
5. Turn off the server
6(any other character). Exit

Without entering Choice № 5 server won't be turned off.
To turn off server enter choice № 5 or press "ctrl+c" while on server terminal. 
