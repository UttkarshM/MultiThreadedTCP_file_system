#include "../libs/Server.h"
/*#include "../libs/Client.h"*/
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

Server::Server* server = new Server::Server();

void* temp(){
  server->accept_tcp();
  int id=0;
  server->chat_to_client(id);
  return nullptr;
}
void* task(void* arg){
  return temp();
}

int main()
{
  struct sockaddr_in new_server[100];
  int index = 0;
  int port = 14000;
  int temp=0;

  std::cout<<pthread_self()<<std::endl;
  server->create_tcp_socket();
  server->reuse_tcp_socket();

  server->bind_tcp_socket(new_server[0],port);

  server->listen_tcp_socket();
  std::cout<<"completed listening"<<endl;
  while(1){
    Server::server_queue_push(task);
  }
  /*for(int i=0;i<Server::top;i++){*/
  /*  Server::server_queue_pop();*/
  /*}*/
  return 0;
}
