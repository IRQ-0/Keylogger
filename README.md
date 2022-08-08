## What is this?

So, basicly this is keylogger written completly in C in time period of one evning.
It works like that:
First, client app connects to server, then, if key is pressed it sends information about it to the server.
Every key is saved to file on server with time signature.
If you are more interested, then check code to learn more about it.

## Compilation and usage
### Note that client app HAS TO BE used under MS Windows and server app under Linux!

It is written in C so you must have ```gcc``` compiler installed.

### Client app
Change IP in ```main.c``` file (line 9) to your server's IP.\
Compilation: ```gcc main.c keys.c socket.c -lws2_32 -o keylogger.exe```\
As a result, it creates exe file ```keylogger.exe``` and this is file you can send to other person to see what he/she is typing.

### Server app
Compilation: ```gcc main.c -o server```\
To run server, just type in terminal ```./server 127.0.0.1```, and it should work.

## This program is written only for educational purpose. Author of this program is not responsible of possible illegal usage of this program!
