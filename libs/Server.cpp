#include "Server.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>

using namespace std;

namespace Server{
  pthread_t readerthreads[100];
  int top = -1;
  int rear = -1;

  
  void Server::create_tcp_socket(){
    int tempsockfd=socket(AF_INET,SOCK_STREAM,0);//tcp  connection
    this->sockfd = tempsockfd; //
    if(sockfd<0){
      logger("socket");
    }
    std::cout<<"socket created successfully \n";
  }
  void Server::reuse_tcp_socket(){

  }

  void Server::bind_tcp_socket(struct sockaddr_in& server,int port){
    server.sin_family=AF_INET;
    server.sin_port=htons(port);
    this->port=port;
    server.sin_addr.s_addr=htonl(INADDR_ANY);

    if(bind(sockfd,(struct sockaddr*)&server,sizeof(server))<0){
      logger("bind");
    }
    std::cout<<"binding was successfull\n";
  }

  void Server::listen_tcp_socket() const{
    if(listen(sockfd,MAX_CLIENTS)<0){
      logger("listening");
    }
  }

  void* Server::accept_tcp(){

    struct sockaddr_in server;
    socklen_t len=sizeof(server);
    new_sock_fd=accept(this->sockfd,(struct sockaddr*)&server,&len);
    this->new_sock_fd = new_sock_fd;
    if(new_sock_fd<0){
      logger("Accepting");
    }

  std::cout<<pthread_self()<<std::endl;
    return nullptr;
  }

  void Server::connect_tcp_socket() const {
    char buffer[255] = "holla";

    write(this->new_sock_fd, buffer, strlen(buffer) + 1); 

    char message[255];
    memset(message, '\0', sizeof(message)); 

    read(this->new_sock_fd, message, sizeof(message)); 

    printf("Received message: %s\n", message);

  }
  void Server::transfer_via_socket(char* buffer){}
}
