#include "../libs/Server.h"
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

using namespace std;

static Server::Server* server = new Server::Server();

static void* temp(){
  server->accept_tcp();
  int id=0;
  char buffer[256];

  /*server->get_file_content(buffer);*/

  /*server->send_image("cat.jpeg");*/
  server->show_directories_files(".");
  /*server->show_directories_files("CMakeLists.txt");*/
  /*server->chat_to_client(id);*/
  /*server->get_file_content("CMakeLists.txt");*/
  sleep(5);
  return nullptr;
}
static void* task(void* arg){
  return temp();
}
int main()
{
  {
    struct sockaddr_in new_server[100];
    int index = 0;
    int port = 14000;
    int temp=0;

    server->create_tcp_socket();
    server->reuse_tcp_socket();

    server->bind_tcp_socket(new_server[0],port);

    server->listen_tcp_socket();
    std::cout<<"completed listening\n";
    while(true){
      Server::server_queue_push(task);
    }
  }
  return 0;
}
