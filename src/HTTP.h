#ifndef __HTTP_H_
#define __HTTP_H_

#include "TCPClient.h"

typedef void (*DataHandler)(const char* response);

int HTTPClient_Post(TCPClient* client, const char* host, const char* path, const char* body, DataHandler data);


#endif /* __HTTP_H_ */