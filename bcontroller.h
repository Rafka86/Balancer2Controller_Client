#ifndef _BCONTROLLER_H_
#define _BCONTROLLER_H_

typedef struct {
	double position;
	double velocity;
	double angle;
	double angular_v;
} DataSet;

extern int Socket;

int Connect(const char* server_addr, const int server_port);
int Disconnect();
int getSensorInfos(const DataSet* data);
int moveLeft();
int moveRight();
int stop();

#endif // _BCONTROLLER_H_
