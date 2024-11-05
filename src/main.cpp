#include "../libs/Server.cpp"
/*#include "../libs/Client.h"*/
#include <netinet/in.h>

using namespace std;

int main()
{
  Server::Server* server = new Server::Server();
  /* Client::Client* client = new Client::Client(); */
  struct sockaddr_in new_server;
  int port = 14000;
  int temp=0;

  server->create_tcp_socket();

  server->bind_tcp_socket(new_server,port);
  server->listen_tcp_socket();
  server->accept_tcp(new_server,temp,temp);//we dont use the last two parameters // remove those later

  server->connect_tcp_socket(new_server);
  return 0;
}
