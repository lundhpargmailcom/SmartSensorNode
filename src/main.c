#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TCPClient.h"
#include "HTTP.h"

void PrintResponse(const char* response_data)
{
    printf("<========Server response========>:\n%s\n", response_data);
}

char* CreateJSONData(const char* device, double temp)
{
    char buffer[256];
    time_t now = time(NULL);
    char timestr[64];
    strftime(timestr, sizeof(timestr), "%Y-%m-%d %H:%M:%S", localtime(&now));

    snprintf(buffer, sizeof(buffer), "{ \"device\": \"%s\", \"time\": \"%s\", \"temperature\": \"%.1f°C\" }",
             device, timestr, temp);

    char* ptr = malloc(strlen(buffer)+1);
    if(!ptr)
    {
        return NULL;
    }

    strcpy(ptr, buffer);

    char** pptr = &ptr;
    return *pptr;
    
}


int main()
{
    TCPClient client;
    TCPClient_Initiate(&client);

    const char* host = "httpbin.org";
    const char* port = "80";
    const char* path = "/";

    printf("Connecting to %s:%s...\n", host, port);
    if(TCPClient_Connect(&client, host, port) != 0)
    {
        fprintf(stderr, "Failed to connect.\n");
        return 1;
    }

    char* body = CreateJSONData("UUID-1234", 6.7);
    if(!body)
    {
        fprintf(stderr, "Failed to create body!\n");
        TCPClient_Dispose(&client);
        return -1;
    }

    printf("Sending POST message:\n%s\n", body);

    HTTPClient_Post(&client, host, port, path, body, PrintResponse);

    free(body);
    TCPClient_Dispose(&client);
    

    return 0;
}