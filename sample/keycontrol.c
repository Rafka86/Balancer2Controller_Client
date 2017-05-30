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
	ML,
	MR,
	RETRY,
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
		case 'r': return RETRY;
		case 'a': return ML;
		case 'd': return MR;
	}
	return UNKNOWN;
}

void control() {
	while (1) {
		if (kbhit()) {
			Key now = getPressedKey();
			switch (now) {
				case LEFT: MoveLeft(); break;
				case ML: Move(10000); break;
				case MR: Move(-10000); break;
				case RIGHT: MoveRight(); break;
				case RETRY: Reset(); break;
				default: Stop(); return;
			}
		}
	}
}

int main() {
	if (Connect(SERVER_ADDR, SERVER_PORT)) return EXIT_FAILURE;

	control();

	if (Disconnect()) return EXIT_FAILURE;
	return 0;
}
