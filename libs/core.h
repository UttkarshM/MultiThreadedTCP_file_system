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

