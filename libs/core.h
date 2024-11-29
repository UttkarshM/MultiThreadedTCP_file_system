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
	/* exit(1) */

#define MAX_CLIENTS 200
#define BUFF_LEN 1024
#define END_MESSAGE_CHARACTER "$exit$"
#define DATA_PATH_SERVER "/home/uttkarsh/Distributed_file_management_system/project/data/server/data/"
#define DATA_PATH_CLIENT "/home/uttkarsh/Distributed_file_management_system/project/data/client/data/"
