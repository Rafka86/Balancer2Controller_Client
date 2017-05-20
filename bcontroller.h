#ifndef _BCONTROLLER_H_
#define _BCONTROLLER_H_

typedef struct {
	double position;
	double velocity;
	double angle;
	double angular_v;
} DataSet;

int Connect(const char* server_addr, const int server_port);
int Disconnect();
int GetSensorInfos(const DataSet* data);
int MoveLeft();
int MoveRight();
int Stop();

#endif // _BCONTROLLER_H_
