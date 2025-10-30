#include "TCPClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>


int TCPClient_Initiate(TCPClient* _Client)
{
    _Client->fd = -1;
    return 0;
}

int TCPClient_Connect(TCPClient* _Client, const char* host, const char* port)
{
    struct addrinfo hints = {0};
	struct addrinfo* res = NULL;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(host, port, &hints, &res) != 0)
        return -1;


    /* The following text is just a rough straight of translation of the text provided to us in the example by our educator.

    getaddrinfo() can provide a linked list of address suggestions for the same host and port.
    For example, a server can have both IPv4 and IPv6-adresses, or multiple network cards.
    
    Every node in the list (struct addrinfo) contains a possible adress to try. 
    If the first address doesn't work (for example connect() fails), then it will try the next.
    */

    int fd = -1;
    struct addrinfo* rp;
    for (rp = res; rp; rp = rp->ai_next)
	{
        fd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (fd < 0)
			continue;

        if (connect(fd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

        close(fd);
        fd = -1;
    }

    freeaddrinfo(res);
    if (fd < 0)
		return -1;

    _Client->fd = fd;
    return 0;
    
}

int TCPClient_Read(TCPClient* _Client, uint8_t* buf, int len)
{
    return recv(_Client->fd, buf, len, 0);
}

int TCPClient_Write(TCPClient* _Client, const uint8_t* buf, int len)
{
    return send(_Client->fd, buf, len, 0);
}

void TCPClient_Disconnect(TCPClient* _Client)
{
    if (_Client->fd >= 0)
		close(_Client->fd);

    _Client->fd = -1;
}

void TCPClient_Dispose(TCPClient* _Client)
{
	TCPClient_Disconnect(_Client);
}