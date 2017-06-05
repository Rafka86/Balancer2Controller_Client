#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "private.h"
#include "lib/packet.h"

int service(int fd) {
  Packet p;
	int n;

	printf("Command waiting.\n");
  if ( (n = recv(fd, &p, sizeof(p), 0)) <= 0 )
    return 0;
	
	switch (p.com) {
		case GET: printf("Command : Get.\tn=%d\n", n); break;
		case MOV: printf("Command : Move %s.\tn=%d\n", (p.data[0] < 0.0) ? "Right" : "Left", n); break;
		case STP: printf("Command : Stop.\tn=%d\n", n); break;
		case RST: printf("Command : Reset.\tn=%d\n", n); break;
	}
	
	if (p.com == GET) {
		if ( send(fd, (char*)&p, sizeof(p), 0) <= 0 )
			return 0;
		printf("Sending message.\n");
	}

  return n;
}

void error_e(const char *s) {
  perror(s);
  exit(1);
}

int main(int argc, char **argv) {
  int sockfd, newfd;
  struct sockaddr_in sin, cli;
  socklen_t clilen;

  if ( (sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
    error_e("cannot create socket");

  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = PF_INET;
  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_port = htons(SERVER_PORT);
  if ( bind(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0 )
    error_e("cannot bind");
  if ( listen(sockfd, 5) < 0 )
    error_e("cannot listen");

	clilen = sizeof(cli);
  printf("Accepting connection\n");
  if ( (newfd = accept(sockfd, (struct sockaddr *)&cli, &clilen)) < 0 )
    error_e("cannot accept");
  printf("Connection estabiished\n");
  
	while ( service(newfd) != 0 );
  printf("Connection closed\n");

	if ( shutdown(newfd, SHUT_RDWR) < 0 )
    error_e("cannot shutdown");
  
	close(newfd);
  close(sockfd);
  return 0;
}
