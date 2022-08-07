#include "socket.h"

SOCKET newSocket(int* errorPtr, char* IP, int port, int cliSrv) {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(result != NO_ERROR) {
		*errorPtr = 2;
	}
	SOCKET mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(mainSocket == INVALID_SOCKET) {
    	*errorPtr = 1;
    	WSACleanup();
	}
	struct sockaddr_in service;
	memset(&service, 0, sizeof(service));
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr(IP);
	service.sin_port = htons(port);
	Sleep(100);
	if (cliSrv == AS_CLIENT) {
		result = connect(mainSocket, (SOCKADDR*) &service, sizeof(service));
		if (result == SOCKET_ERROR) {
			*errorPtr = 5;
			WSACleanup();
			return mainSocket;
		} else {
			return mainSocket;
		}
	} else {
		if(bind(mainSocket,(SOCKADDR*) &service, sizeof(service)) == SOCKET_ERROR) {
    		closesocket(mainSocket);
    		*errorPtr = 3;
    	}
    	if(listen(mainSocket, 1) == SOCKET_ERROR) {
    		*errorPtr = 4;
		}
		*errorPtr = 0;
		return mainSocket;
	}
}

int takeData(SOCKET mainSocket, char* data, int maxSize) {
	int i, bytesRecv = SOCKET_ERROR;
	char * recvbuf = malloc(sizeof(char) * maxSize);
	for (i = 0; i < maxSize; i++) {
		recvbuf[i] = '\0';
	}
	bytesRecv = recv(mainSocket, recvbuf, maxSize, 0);
	strcpy(data, recvbuf);
	return bytesRecv;
}

void sendData(SOCKET mainSocket, char* data) {
	send(mainSocket, data, strlen(data), 0);
}
