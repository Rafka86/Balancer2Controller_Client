#ifndef _PACKET_H_
#define _PACKET_H_

typedef enum {
	GET,
	MVR,
	MVL,
	STP
} Command;
#define MAX_DATA_SIZE 4
typedef struct {
	Command com;
	double data[MAX_DATA_SIZE];
} Packet;

#endif // _PCAKET_H_
