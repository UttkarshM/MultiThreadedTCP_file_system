/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/
/*#define STB_IMAGE_IMPLEMENTATION*/

#include "Server.h"

#include <cstdio>
#include <iterator>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
#include "../external/stb_image.h"
#include "../external/stb_image_write.h"

using namespace std;

namespace Server{
  pthread_t readerthreads[100];
  int top = -1;
  int rear = -1;
    void server_queue_push(void* function(void*)) {
        if (pthread_create(&readerthreads[++top], NULL, function, NULL) != 0) {
            std::cerr << "Error: Failed to create thread" << std::endl;
            --top; 
        } else {
            server_queue_pop();
        }
    }

    void server_queue_pop() {
        if (pthread_join(readerthreads[++rear], NULL) != 0) {
            std::cerr << "Error: Failed to join thread" << std::endl;
            --rear; 
        }
    }

  void Server::create_tcp_socket(){
    int tempsockfd=socket(AF_INET,SOCK_STREAM,0);//tcp  connection
    this->sockfd = tempsockfd; //
    if(sockfd<0){
      logger("socket");
    }
    std::cout<<"socket created successfully \n";
  }
  void Server::reuse_tcp_socket(){
    int opt=1;
    if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt))){
      cout<<"SETSOCKOPT\n";//this is for reusing a port if its not free and is dealing with another
      /*exit(1);*/
    }
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
  void* Server::accept_tcp() {
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);
    new_sock_fd = accept(sockfd, (struct sockaddr*)&client_addr, &len); 

    if (new_sock_fd < 0) {
      logger("Failed to accept connection");
    } else {
      std::cout << "Connection accepted from client\n";
    }

    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
    std::cout << "Client connected from IP: " << client_ip << " on port: " << ntohs(client_addr.sin_port) << std::endl;

    return nullptr;  // You can return whatever is needed here
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

  void Server::chat_to_client(int id) {
    char buffer[BUFF_LEN];

    ssize_t bytes_read = read(this->new_sock_fd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
      std::cerr << "Failed to read message from client \n";
      return;
    }

    std::cout << "Received message from client: " << buffer << "\n";

    std::cout << "Enter the message to be sent\n";
    std::cin.getline(buffer, sizeof(buffer));
    ssize_t bytes_written = write(this->new_sock_fd, buffer, sizeof(buffer));
    
    if (bytes_written < 0) {
      std::cerr << "Failed to send message to client \n";
      return;
    }
    memset(buffer, '\0', sizeof(buffer));
  }

void Server::get_file_content(char* buff) const {
    char buffer[BUFF_LEN] = {0};
    std::fstream f_obj;
    f_obj.open(buff, std::ios::in);

    memset(buffer,'\0',sizeof(buffer));
    strcpy(buff,DATA_PATH_CLIENT);

    if (!f_obj.is_open()) {
        std::cerr << "Error opening file: " << buff << std::endl;
        return;
    }
    std::string file_lines;
    while (getline(f_obj, file_lines)) {
        memset(buffer, '\0', sizeof(buffer));
        strcpy(buffer, file_lines.c_str());
        write(this->new_sock_fd, buffer, sizeof(buffer));
    }

    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, END_MESSAGE_CHARACTER);
    write(this->new_sock_fd, buffer, sizeof(buffer));
    f_obj.close();
}

void Server::show_directories_files(char* path) {
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    std::cout << "Current working directory: " << cwd << std::endl;
    std::cout << "Trying to open directory: " << path << std::endl;

    DIR* dir = opendir(path);
    if (!dir) {
        perror("opendir error");
        std::cerr << "Error: Unable to open directory " << path << std::endl;
        return;
    }



    dir = opendir(DATA_PATH_SERVER);
    if (!dir) {
        std::cerr << "Error: Unable to open directory " << path << std::endl;
        return;
    }

    char buffer[BUFF_LEN] = {0};
    struct dirent* en;

    while ((en = readdir(dir)) != NULL) {
        std::string file_name = en->d_name;
        if (file_name != "." && file_name != "..") {
            memset(buffer, '\0', sizeof(buffer));
            strcpy(buffer, file_name.c_str());
            write(this->new_sock_fd, buffer, sizeof(buffer));
        }
    }

    memset(buffer, '\0', sizeof(buffer));
    strcpy(buffer, END_MESSAGE_CHARACTER);
    write(this->new_sock_fd, buffer, sizeof(buffer));

    read(this->new_sock_fd, buffer, sizeof(buffer));
    get_file_content(buffer);
    closedir(dir);
}


  unsigned char* Server::send_image(char* file_path) {
    show_directories_files(file_path);

    int width, height, channels;
    unsigned char* img = stbi_load(file_path, &width, &height, &channels, 0);
    if(img == NULL){
      printf("Error in loading the image \n");
    }
    std::cout<<width<<" - "<<height<<" - "<<channels<<"\n";
    stbi_image_free(img);
    return img; 
  }

  bool Server::write_image(char* img_data,char* path,int width,int height,int channels){
    stbi_write_png(path, width, height, channels, img_data, width * channels);
    return true;
  }


}

