
#include "Client.h"
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include "../external/stb_image.h"
#include "../external/stb_image_write.h"
#include "Server.h"

/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/
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

    
    memset(buffer, '\0', sizeof(buffer));
    
    ssize_t bytes_read = read(this->sockfd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        std::cerr << "Failed to read message from server" << std::endl;
        return;
    }

    std::cout << "Message received from server: " << buffer << "\n";
}

void Client::get_file_content(const char* buff) const {

    char buffer[BUFF_LEN] = {0};
    std::string paths = DATA_PATH_CLIENT;
    paths+="_copy_";
    paths+=buff;
    std::fstream file(paths.c_str(),std::ios::out|std::ios::app);
    file.write("",0);
    while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
        memset(buffer, '\0', sizeof(buffer));
        read(this->sockfd, buffer, sizeof(buffer));
        if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) { 
            /*std::cout << buffer << "\n"; // Print file content*/
        file<<buffer<<std::endl;
        }
    }
    std::cout << "File transfer completed.\n";
}

void Client::get_file_names() const {
    char buffer[BUFF_LEN] = {0};
    while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
        memset(buffer, '\0', sizeof(buffer));
        read(this->sockfd, buffer, sizeof(buffer));
        if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
            std::cout << buffer << "\n"; // Print file name
        }
    }
    /*std::cout << "File list received.\n";*/
    std::string file;
    std::cout << "Enter the file name: ";
    std::cin >> file;
    write(this->sockfd, file.c_str(), file.size());
    get_file_content(file.c_str());
}

  unsigned char* Client::send_image(char* file_path) {
    int width, height, channels;
    unsigned char* img = stbi_load(file_path, &width, &height, &channels, 0);
    if(img == NULL){
      printf("Error in loading the image \n");
      /*exit(1);*/
    }
    stbi_image_free(img);
    return img; 
  }
  bool Client::write_image(char* img_data,char* path,int width,int height,int channels){

    stbi_write_png(path, width, height, channels, img_data, width * channels);
    return true;
  }

}
