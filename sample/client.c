#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "private.h"
#include "lib/bcontroller.h"

#define BUFSIZE 1024

void error_e(const char *s) {
  perror(s);
  exit(1);
}

void client() {
	DataSet set;
  char buf[BUFSIZE];
  int n;

	printf("Command : get mover movel stop\n");
  while (fgets(buf, BUFSIZE, stdin) != NULL) {
    n = strlen(buf);
    buf[n - 1] = '\0';
    
		if (strcmp(buf, "get") == 0) {
			if (GetSensorInfos(&set)) error_e("Faild communication.");
		} else if (strcmp(buf, "mover") == 0) {
			if (MoveRight()) error_e("Faild communication.");
		} else if (strcmp(buf, "movel") == 0) {
			if (MoveLeft()) error_e("Faild communication.");
		} else if (strcmp(buf, "stop") == 0) {
			if (Stop()) error_e("Faild communication.");
		} else {
			fprintf(stderr, "Undefined command.\n");
			return;
		}

		printf("Command : get mover movel stop\n");
  }
}

int main(int argc, char **argv) {
  if (Connect(SERVER_ADDR, SERVER_PORT)) error_e("Cannot connect.");
	printf("Connected.\n");
	
	client();

  if (Disconnect()) error_e("cannot shutdown");
	printf("Disconnected.\n");

  return 0;
}
