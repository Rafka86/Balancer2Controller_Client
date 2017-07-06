#ifndef _BB2C4RL_H_
#define _BB2C4RL_H_

typedef struct {
	int count;
	double time;
	double position;
	double velocity;
	double angle;
	double angular_v;
} DataSet;

int Connect();
int Disconnect();
int GetSensorInfos(DataSet* data);
int Move(const double spd);
int MoveLeft(const double spd);
int MoveRight(const double spd);
int Stop();
int Reset();

#endif // _BCONTROLLER_H_
