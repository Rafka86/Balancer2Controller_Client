#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#include "private.h"
#include "lib/bcontroller.h"
#include "lib/packet.h"

typedef enum {
	LEFT,
	RIGHT,
	UNKNOWN
} Key;

int kbhit() {
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

Key getPressedKey() {
	switch (getchar()) {
		case 0x1b:
			switch(getchar()) {
				case 0x5b:
					switch(getchar()) {
						case 0x43: return RIGHT;
						case 0x44: return LEFT;
					}
					break;
			}
			break;
	}
	return UNKNOWN;
}

void control() {
	Key old = UNKNOWN;
	//DataSet data;

	while (1) {
		/*int stat = GetSensorInfos(&data);
		if (stat == EXIT_FAILURE) return;
		else if (stat == TURNOVER) {
			fprintf(stderr, "Balancer is turn over.\n");
			fprintf(stderr, "Retry? (y/n) : ");
			char ans;
			if (kbhit()) ans = getchar();
			if (ans == 'y') {
				if (Reset()) return;
			} else {
				if (MoveRight()) return;
			}
		}*/
		if (kbhit()) {
			Key now = getPressedKey();
			if (old != now) {
				switch (now) {
					case LEFT: MoveLeft(); break;
					case RIGHT: MoveRight(); break;
					default: Stop(); return;
				}
			}
			old = now;
		}
	}
}

int main() {
	if (Connect(SERVER_ADDR, SERVER_PORT)) return EXIT_FAILURE;

	control();

	if (Disconnect()) return EXIT_FAILURE;
	return 0;
}
