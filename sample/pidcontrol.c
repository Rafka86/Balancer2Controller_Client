#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "private.h"
#include "lib/bcontroller.h"

void pidcontrol() {
	DataSet s;
	int i;

	for (i = 0; i < 10; i++) {
		if (GetSensorInfos(&s)) return;
		printf("POS:%lf\n", s.position);
		printf("VEL:%lf\n", s.velocity);
		printf("ANG:%lf\n", s.angle);
		printf("ASP:%lf\n", s.angular_v);
		sleep(2);
	}
}

int main() {
	if (Connect(SERVER_ADDR, SERVER_PORT)) return EXIT_FAILURE;

	pidcontrol();

	if (Disconnect()) return EXIT_FAILURE;
	return 0;
}
