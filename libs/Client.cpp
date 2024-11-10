
#include "Client.h"
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

namespace Client {

  sem_t x, y;
  pthread_t tid;
  pthread_t readerthreads[100];
  int readercount = 0;

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
    client.sin_addr.s_addr = INADDR_ANY;//converts newtwork address(generally) into readable string from ipv4;
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
  void Client::chat_to_server() {
    char buffer[BUFF_LEN];
    
    std::cout << "Enter the message to be sent\n";
    std::cin.getline(buffer, sizeof(buffer));

    ssize_t bytes_written = write(this->sockfd, buffer, strlen(buffer) + 1);
    if (bytes_written < 0) {
        std::cerr << "Failed to send message to server" << std::endl;
        return;
    }
    
    memset(buffer, '\0', sizeof(buffer));
    
    ssize_t bytes_read = read(this->sockfd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        std::cerr << "Failed to read message from server" << std::endl;
        return;
    }

    std::cout << "Message received from server: " << buffer << "\n";
}

}
