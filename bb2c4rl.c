#include <stdio.h>			//printf, fprintf, perror
#include <stdlib.h>			//atoi, exit, EXIT_FAILURE, EXIT_SUCCESS
#include <math.h>
#include <bb2d.h>

#include "bb2c4rl.h"

#define ADDR_COUNT 120
#define ADDR_TIME  128
#define ADDR_POS   136
#define ADDR_VEL   144
#define ADDR_ANGLE 152
#define ADDR_ANG_V 160

#define READ_SIZE 48
#define READ_FROM ADDR_COUNT

#define ADDR_TARGET_SPD 168

#define ANGLE_LIMIT_DEGREE 15.0
#define ANGLE_LIMIT        (ANGLE_LIMIT_DEGREE * M_PI / 180.0)

int bb2c4rl_error(const char* sentence) {
	perror(sentence);
	return EXIT_FAILURE;
}

int Connect() {
  int res = BB2D_Init();
	if (res) return bb2c4rl_error("BB2Driver Init Error.");

  res = BB2D_Connect();
	if (res) return bb2c4rl_error("BB2Driver Connect Error.");

	return EXIT_SUCCESS;
}

int Disconnect() {
  int res = BB2D_Disconnect();
	if (res) return bb2c4rl_error("BB2Driver Disconnect Error.");

  res = BB2D_Exit();
	if (res) return bb2c4rl_error("BB2Driver Exit Error.");

	return EXIT_SUCCESS;
}

int GetSensorInfos(DataSet* set) {
  int res = BB2D_Read(READ_FROM, READ_SIZE);
  if (res) return bb2c4rl_error("BB2Driver Read Error.");

	set->count     = (int)BB2D_GetDouble(ADDR_COUNT);
	set->time      =      BB2D_GetDouble(ADDR_TIME);
	set->position  =      BB2D_GetDouble(ADDR_POS);
	set->velocity  =      BB2D_GetDouble(ADDR_VEL);
	set->angle     =      BB2D_GetDouble(ADDR_ANGLE);
	set->angular_v =      BB2D_GetDouble(ADDR_ANG_V);

  if (set->angle < -ANGLE_LIMIT || ANGLE_LIMIT < set->angle) return TURNOVER;

	return EXIT_SUCCESS;
}

int Move(const double spd) {
  int res = BB2D_WriteDouble(ADDR_TARGET_SPD, spd);
  if (res) return bb2c4rl_error("BB2Driver Write Error.");

	return EXIT_SUCCESS;
}

int MoveRight(const double spd) {
	return Move(-spd);
}

int MoveLeft(const double spd) {
	return Move(spd);
}

int Stop() {
  int res = BB2D_WriteDouble(ADDR_TARGET_SPD, 0.0);
  if (res) return bb2c4rl_error("BB2Driver Write Error.");

	return EXIT_SUCCESS;
}

int Reset() {
	return EXIT_SUCCESS;
}
