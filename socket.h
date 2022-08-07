#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#define AS_SERVER 0
#define AS_CLIENT 1

SOCKET newSocket(int*, char*, int, int);
void closeSocket(SOCKET);
int takeData(SOCKET, char*, int);
void sendData(SOCKET, char*);
