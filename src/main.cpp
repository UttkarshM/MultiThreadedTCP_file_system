#include "../libs/Server.h"

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
    #include <pthread.h>
    #include <unistd.h>
#endif

using namespace std;

static Server::Server* server = new Server::Server();

static void* temp(){
  server->accept_tcp();
  int id=0;
  char buffer[256];

  char path[] = ".";
  server->show_directories_files(path);
  return nullptr;
}
static void* task(void* arg){
  return temp();
}
int main()
{
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
#endif

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

#ifdef _WIN32
    WSACleanup();
#endif
  return 0;
}
