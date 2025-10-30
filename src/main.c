#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "TCPClient.h"
#include "HTTP.h"

void PrintResponse(const char* data)
{
    printf("Server response:\n%s\n", data);
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

    if(TCPClient_Connect(&client, "httpbin.org", "80") != 0)
    {
        fprintf(stderr, "Failed to connect.\n");
        return 1;
    }

    char* body = CreateJSONData("UUID-1234", 6.7);
    HTTPClient_Post(&client, "httpbin.org", "/", body, PrintResponse);

    free(body);
    TCPClient_Dispose(&client);
    

    return 0;
}