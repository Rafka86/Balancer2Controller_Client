#include <stdio.h>			//printf, fprintf, perror
#include <stdlib.h>			//atoi, exit, EXIT_FAILURE, EXIT_SUCCESS
#include <string.h>			//memset
#include <sys/socket.h>	//socket, connect, recv
#include <arpa/inet.h>	//struct sockaddr_in, struct_sockaddr, inet_ntoa, inet_aton
#include <unistd.h>			//close
#include <netdb.h>			//hostent, gethostbyname

#include "bcontroller.h"
#include "packet.h"

#define SOCK_INIT -1

int Socket = SOCK_INIT;

int error(const char* sentence) {
	perror(sentence);
	return EXIT_FAILURE;
}

int Connect(const char* addr, const int port) {
	if (Socket != SOCK_INIT) return error("Already made a socket.");

	Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (Socket < 0) return error("Cannot create socket.");

	struct sockaddr_in serverSockAddr;
	memset(&serverSockAddr, 0, sizeof(serverSockAddr));
	serverSockAddr.sin_family = AF_INET;
	serverSockAddr.sin_addr.s_addr = inet_addr(addr);
	if (serverSockAddr.sin_addr.s_addr < 0) {
		struct hostent *host;
		host = gethostbyname(addr);
		if (host == NULL) return error("Cannot solve host name.");
		serverSockAddr.sin_addr.s_addr = *(unsigned int *)host->h_addr_list[0];
	}
	if (port < 10000) return error("Not recommended port number.");
	serverSockAddr.sin_port = htons(port);

	int stat = connect(Socket, (struct sockaddr*)&serverSockAddr, sizeof(serverSockAddr));
	if (stat < 0) return error("Cannot connect to host.");

	fprintf(stderr, "Connect to %s.\tPort : %d\n", addr, port);
	return 0;
}

int Disconnect() {
	if (Socket == SOCK_INIT) return error("Socket has not created yet.");

	close(Socket);
	fprintf(stderr, "Connection closed.\n");
	Socket = SOCK_INIT;

	return 0;
}

int GetSensorInfos(const DataSet* set) {
	if (Socket == SOCK_INIT) return error("Socket has not created yet.");

	Packet p;

	p.com = GET;
	if (send(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");

	if (recv(Socket, &p, sizeof(p), 0) <= 0) return error("Faild recv packet.");
	set->position  = p.data[0];
	set->velocity  = p.data[1];
	set->angle     = p.data[2];
	set->angular_v = p.data[3];

	return 0;
}

int MoveRight() {
	if (Socket == SOCK_INIT) return error("Socket has not created yet.");

	Packet p;

	p.com = MVR;
	if (send(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	if (recv(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	printf("Receive feedback.\n");

	return 0;
}

int MoveLeft() {
	if (Socket == SOCK_INIT) return error("Socket has not created yet.");

	Packet p;

	p.com = MVL;
	if (send(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	if (recv(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	printf("Receive feedback.\n");

	return 0;
}

int Stop() {
	if (Socket == SOCK_INIT) return error("Socket has not created yet.");

	Packet p;

	p.com = STP;
	if (send(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	if (recv(Socket, &p, sizeof(p), 0) <= 0) return error("Faild send packet.");
	printf("Receive feedback.\n");

	return 0;
}
