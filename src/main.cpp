#include "../libs/Server.h"
/*#include "../libs/Client.h"*/
#include <netinet/in.h>
#include <pthread.h>

using namespace std;

Server::Server* server = new Server::Server();

void* temp(){
  server->listen_tcp_socket();
  server->accept_tcp();
  server->connect_tcp_socket();
  return nullptr;
}
void* task(void* arg){
  return temp();
}

int main()
{
  /* Client::Client* client = new Client::Client(); */
  struct sockaddr_in new_server[100];
  int index = 0;
  int port = 14000;
  int temp=0;

  std::cout<<pthread_self()<<std::endl;
  server->create_tcp_socket();

  server->bind_tcp_socket(new_server[0],port);
  while(1){
    /*server->listen_tcp_socket();*/
  
  /*server->accept_tcp();*/
  ;//we dont use the last two parameters // remove those later
   //

    Server::server_queue_push(task);
  /*Server::server_queue_pop();*/
  /*server->accept_tcp(new_server,temp,temp);//we dont use the last two parameters // remove those later*/
    /*server->connect_tcp_socket();*/
  }
  for(int i=0;i<Server::top;i++){
    Server::server_queue_pop();
  }
  return 0;
}
