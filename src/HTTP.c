#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HTTP.h"


int HTTPClient_Post(TCPClient* client, const char* host, const char* port, const char* path, const char* body, DataHandler data)
{
    char request[1024];
    snprintf(request, sizeof(request), 
        "POST %s HTTP/1.1\r\n"
        "Host: %s\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %zu\r\n"
        "\r\n"
        "%s", path, host, strlen(body), body);
        
    if(TCPClient_Write(client, (const uint8_t*)request, strlen(request)) < 0)
    {
        perror("send");
        return -1;
    }

    shutdown(client->fd, SHUT_WR);

    uint8_t response[4096];
    int total = 0;

    while(1)
    {
        int n = TCPClient_Read(client, response, sizeof(response) - 1);
        if(n <= 0)
        {
           break;
        }
        response[n] = '\0';
        data((const char*)response);
        total += n;
    }
    
    if(total == 0)
    {
        printf("No data received\n");
    }

    return 0;
}