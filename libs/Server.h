#pragma once
#include "core.h"
#include <unistd.h>

namespace Server {
extern sem_t x, y;
extern pthread_t tid;
extern pthread_t readerthreads[100];
extern int readercount;

void* reader(void* param);
void* writer(void* param);

class Server{
  public:
    Server()
      :sockfd(-1),new_sock_fd(-1),
      port(8080)
    {
    }
		~Server(){
			close(new_sock_fd);
		}
    void create_tcp_socket();
    void reuse_tcp_socket();
		void bind_tcp_socket(struct sockaddr_in& server,int port);
		void listen_tcp_socket() const;
		void accept_tcp(struct sockaddr_in& server,int& new_sock_fd,socklen_t len);
    void connect_tcp_socket(struct sockaddr_in& client) const ;
    void transfer_via_socket(char* buffer);
  private:
    int sockfd,new_sock_fd;
    int port;
    struct sockaddr_in servaddr;
};
} 
