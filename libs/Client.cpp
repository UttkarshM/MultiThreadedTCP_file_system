
#include "Client.h"
#include <iostream>
#include <string.h>

namespace Client {

  sem_t x, y;
  pthread_t tid;
  pthread_t readerthreads[100];
  int readercount = 0;

  void* reader(void* param)
  {
    sem_wait(&x);
    readercount++;

    if (readercount == 1) {
      sem_wait(&y);
    }
    sem_post(&x);
    printf("\n%d reader is inside", readercount);

    sleep(5);

    sem_wait(&x);
    readercount--;

    if (readercount == 0) {
      sem_post(&y);
    }
    printf("\n%d Writer is leaving", readercount + 1);
    pthread_exit(nullptr);
  }
  void* writer(void* param)
  {
    printf("\nWriter is trying to enter");
    sem_wait(&y);
    printf("\nWriter has entered");
    sem_post(&y);
    printf("\nWriter is leaving");
    pthread_exit(nullptr);
  }
  void Client::create_tcp_socket(){
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->sockfd < 0) {
      logger("socket");
    }
    std::cout << "socket created successfully \n";
  }
  void Client::reuse_tcp_socket(){
  } 
  void Client::connect_tcp_socket(struct sockaddr_in& client,int port){
    memset(&client,'\0',sizeof(client));
    client.sin_family = AF_INET;
    client.sin_port = htons(port);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");//converts newtwork address(generally) into readable string from ipv4;
    this->port = port;

    if(connect(sockfd, (struct sockaddr*)&client, sizeof(client)) < 0)
    {
      logger ("connecting");
    }
    std::cout << "connection has been established successfully\n";
  }
  void Client::transfer_via_socket(char* buffer){
    
    std::cout<<this->sockfd<<std::endl;
      write(this->sockfd, buffer, strlen(buffer) + 1); 

      char message[255];
      memset(message, '\0', sizeof(message)); 

      read(this->sockfd, message, sizeof(message)); 

      printf("Received message: %s\n", message);



  }
}  // namespace Client
