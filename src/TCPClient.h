#ifndef __TCPCLIENT_H_
#define __TCPCLIENT_H_

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


typedef struct
{
    int fd;

} TCPClient;

int TCPClient_Initiate(TCPClient* _Client);

int TCPClient_Connect(TCPClient* _Client, const char* host, const char* port);

int TCPClient_Read(TCPClient* _Client, uint8_t* buf, int len);

int TCPClient_Write(TCPClient* _Client, const uint8_t* buf, int len);

void TCPClient_Disconnect(TCPClient* _Client);

void TCPClient_Dispose(TCPClient* _Client);


#endif /* __TCPCLIENT_H_ */