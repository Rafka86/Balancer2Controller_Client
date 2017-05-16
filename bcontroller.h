#ifndef _BCONTROLLER_H_
#define _BCONTROLLER_H_

#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_ADDR "192.168.12.134"
#define SERVER_PORT 14706

int Connect(const char* server_addr, const int server_port);

#endif // _BCONTROLLER_H_
