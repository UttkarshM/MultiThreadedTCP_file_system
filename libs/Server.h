#pragma once
#include "core.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>

namespace Server {
extern int top;
extern int rear;
extern int thread_no;
extern sem_t x, y;
extern pthread_t tid;
extern pthread_t readerthreads[100];
extern int readercount;
extern int queue[1024*1024]; //apparently the hard limit
void* reader(void* param);
void* writer(void* param);

/*typedef void* (*func_ptr_t)();*/
/*func_ptr_t get_funct_ptr();*/


class Server{
  private:
  public:
    Server()
      :sockfd(-1),new_sock_fd(-1),port(8080)
    {
    }
    ~Server(){
    close(sockfd);
      /*close(new_sock_fd);*/
    }
    void create_tcp_socket();
    void reuse_tcp_socket();
    void bind_tcp_socket(struct sockaddr_in& server,int port);
    void listen_tcp_socket() const;
    /*void accept_tcp();*/
    void* accept_tcp();
    void return_ptr(void* arg);
    void connect_tcp_socket() const ;
    void transfer_via_socket(char* buffer);
    void chat_to_client(int id);
  private:
    int sockfd,new_sock_fd;
    int port;
    struct sockaddr_in servaddr;
};

static void server_queue_pop(){
  /*pthread_t pid = readerthreads[++rear];*/

    /*while(1);*/
  pthread_join(readerthreads[++rear],NULL);
}
static void server_queue_push(void* function(void*)){
  /*std::cout<<top<<"\n";*/
  pthread_create(&readerthreads[++top],NULL,function,NULL);
  /*std::cout<<pthread_self()<<"\n";*/
  server_queue_pop();
}
}
