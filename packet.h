#ifndef _PACKET_H_
#define _PACKET_H_

enum Command {
	GET,
	MOV,
	STP,
	RST
};
#define MAX_DATA_SIZE 4
typedef struct {
	int com;
	double data[MAX_DATA_SIZE];
} Packet;

#endif // _PCAKET_H_
