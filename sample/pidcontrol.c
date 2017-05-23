#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "private.h"
#include "lib/bcontroller.h"

#define SPD_LIM 32767.0
#define SPD_MIN 400.0
#define CONTROL_LOOP 1000
#define GAIN -500.0
#define KP 1.0
#define KI 0.5
#define KD 0.0

void pidcontrol() {
	DataSet s;
	double ang_i, spd;
	int i;

	ang_i = 0.0;
	for (i = 0; i < CONTROL_LOOP; i++) {
		spd = 0.0;
		if (GetSensorInfos(&s)) return;
		
		ang_i += s.angle;
		printf("%f\t%f\t%f\n", s.angle, ang_i, s.angular_v);
		spd = KP * s.angle + KI * ang_i + KD * s.angular_v;
		spd *= GAIN;
		spd = (-SPD_MIN < spd && spd < 0) ? -SPD_MIN : (0 < spd && spd < SPD_MIN) ? SPD_MIN : spd;
		spd = (spd > SPD_LIM) ? SPD_LIM : (spd < -SPD_LIM) ? -SPD_LIM : spd;

		if (Move(spd)) return;
		usleep(200000);
	}
	if (Stop()) return;
}

int main() {
	if (Connect(SERVER_ADDR, SERVER_PORT)) return EXIT_FAILURE;

	pidcontrol();

	if (Disconnect()) return EXIT_FAILURE;
	return 0;
}
