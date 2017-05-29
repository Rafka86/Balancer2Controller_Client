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

	printf("Command : get mover movel stop reset\n");
	while (fgets(buf, BUFSIZE, stdin) != NULL) {
		n = strlen(buf);
		buf[n - 1] = '\0';
    
		if (strcmp(buf, "get") == 0) {
			int stat = GetSensorInfos(&set);
			if (stat == EXIT_FAILURE) error_e("Faild communication.");
			printf("position:%lf\n", set.position);
			printf("velocity:%lf\n", set.velocity);
			printf("angle:%lf\n", set.angle);
			printf("angular_v:%lf\n", set.angular_v);
			if (stat == TURNOVER) {
				fprintf(stderr, "Balancer is turn over.\n");
				fprintf(stderr, "Retry? (y/n) : ");
				fgets(buf, BUFSIZE, stdin);
				buf[strlen(buf) - 1] = '\0';
				if (strcmp(buf, "y") == 0) {
					if (Reset()) error_e("Faild communication.");
				} else {
					if (MoveRight()) error_e("Faild communication.");
				}
			}
		} else if (strcmp(buf, "mover") == 0) {
			if (MoveRight()) error_e("Faild communication.");
		} else if (strcmp(buf, "movel") == 0) {
			if (MoveLeft()) error_e("Faild communication.");
		} else if (strcmp(buf, "stop") == 0) {
			if (Stop()) error_e("Faild communication.");
		} else if (strcmp(buf, "reset") == 0) {
			if (Reset()) error_e("Faild communication.");
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
