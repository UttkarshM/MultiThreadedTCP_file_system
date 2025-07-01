//####Includes####//
#include <arpa/inet.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

//####defines####//
#define logger(x) \
	std::cout<<x<<"\n" 

#define MAX_CLIENTS 200
#define BUFF_LEN 1024
#define END_MESSAGE_CHARACTER "$exit$"
#define DATA_PATH_SERVER "./data/server/data/"
#define DATA_PATH_CLIENT "./data/client/data/"
