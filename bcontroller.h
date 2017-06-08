#ifndef _BCONTROLLER_H_
#define _BCONTROLLER_H_

#define PACKET_LOST 3
#define TURNOVER 2
#define MV_SPD 5.0

typedef struct {
	int count;
	double position;
	double velocity;
	double angle;
	double angular_v;
	double time_stamp;
} DataSet;

int Connect(const char* server_addr, const unsigned short server_port);
int Disconnect();
int GetSensorInfos(DataSet* data);
int Move(const double spd);
int MoveLeft();
int MoveRight();
int Stop();
int Reset();

#endif // _BCONTROLLER_H_
