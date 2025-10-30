#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HTTP.h"


int HTTPClient_Post(TCPClient* client, const char* host, const char* path, const char* body, DataHandler data)
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
        return -1;
    }

    uint8_t response[1024];
    int n = TCPClient_Read(client, response, sizeof(response)-1);
    if(n <= 0)
    {
        return -1;
    } 

    response[n] = '\0';
    data((const char*)response);

    return 0;
}