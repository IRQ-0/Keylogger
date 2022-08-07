#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>

#define PORT 5175

void getTime(char*);

int main(int argc, char ** argv) {
  if (argc < 2) {
    puts("Usage: ./server <IP>");
    exit(2);
  }
  struct sockaddr_in serverAddr;
  struct sockaddr_in secAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  
  if (inet_pton(AF_INET, argv[1], & serverAddr.sin_addr) <= 0) {
    puts("ERROR inet_pton()");
    exit(1);
  }
  
  int srvSock = socket(AF_INET, SOCK_STREAM, 0);
  if (srvSock < 0) {
    puts("ERROR socket()");
    exit(2);
  }
  
  int yes = 1;
  if (setsockopt(srvSock, SOL_SOCKET, SO_REUSEADDR, & yes, sizeof(yes)) == -1) {
    puts("ERROR setsockopt()");
    exit(6);
  }
  
  socklen_t len = sizeof(serverAddr);
  if (bind(srvSock, (struct sockaddr * ) & serverAddr, len) < 0) {
    puts("ERROR bind()");
    exit(3);
  }
  
  if (listen(srvSock, 0) < 0) {
    puts("ERROR listen()");
    exit(4);
  }
  
  printf("Waiting for connection...\n");
  struct sockaddr_in cliAddr = {};
  
  int cliSock = accept(srvSock, (struct sockaddr * ) & cliAddr, & len);
  
  printf("Connected! %s\n", inet_ntoa(cliAddr.sin_addr));

  for ( ; ; ) {
    char buffer[1000];
    char timebuffer[1000];
    memset(timebuffer, 0, sizeof(timebuffer));
    getTime(timebuffer);
    FILE *f;
    f = fopen(timebuffer, "w");
    for ( ; ; ) {
      memset(buffer, 0, sizeof(buffer));
      if (recv(cliSock, buffer, sizeof(buffer), 0) >= 0) {
	fputs(buffer, f);
	printf("%s", buffer);
	fflush(f);
      } else {
	fclose(f);
	break;
      }
    }
  }

  return 0;
}

void getTime(char* buffer) {
  memset(buffer, 0, sizeof(buffer));
  time_t rawtime;
  struct tm* timeinfo;
  time(&rawtime);
  strcpy(buffer, ctime(&rawtime));
  for (int i = 0; i < strlen(buffer); i++) {
    if (buffer[i] == ' ' | buffer[i] == ':') {
      buffer[i] = '_';
    }
  }
  buffer[strlen(buffer) - 1] = '\0';
}
