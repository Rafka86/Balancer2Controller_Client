#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "private.h"

#define BUFSIZE 1024

void client(int fd)
{
  char buf[BUFSIZE];
  int n;

  while (fgets(buf, BUFSIZE, stdin) != NULL)
  {
    n = strlen(buf);
    buf[n - 1] = '\0';
    if (write(fd, buf, n) <= 0) return;
    if (read(fd, buf, n) <= 0) return;
    printf("%s\n", buf);
  }
}

void error(char *s)
{
  perror(s);
  exit(1);
}

int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in sin;

  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    error("cannot create socket");

  bzero((char *)&sin, sizeof(sin));
  sin.sin_family = PF_INET;
  sin.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  sin.sin_port = htons(SERVER_PORT);
  if (connect(sockfd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    error("cannot connect");
	
	char buf[BUFSIZE];
	printf("Connected.\n");
  //if (write(sockfd, "Hello.", BUFSIZE) <= 0) error("cannot write");
  if (read(sockfd, buf, BUFSIZE) <= 0) error("cannot read");
	printf("%s\n", buf);

  if (shutdown(sockfd, SHUT_RDWR) < 0)
    error("cannot shutdown");
  close(sockfd);
	printf("Disconnected.\n");

  return 0;
}
