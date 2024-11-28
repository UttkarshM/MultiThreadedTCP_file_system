/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/
/*#define STB_IMAGE_IMPLEMENTATION*/

#include "Server.h"

#include <cstdio>
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
            --top; // Rollback increment
        } else {
            server_queue_pop();
        }
    }

    void server_queue_pop() {
        if (pthread_join(readerthreads[++rear], NULL) != 0) {
            std::cerr << "Error: Failed to join thread" << std::endl;
            --rear; // Rollback increment
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
    ssize_t bytes_written = write(this->new_sock_fd, buffer, strlen(buffer) + 1);
    if (bytes_written < 0) {
      std::cerr << "Failed to send message to client \n";
      return;
    }
    memset(buffer, '\0', sizeof(buffer));
  }
  void Server::get_file_content(char* buff) const {

    char buffer[BUFF_LEN];
    std::cout<<top<<std::endl;


    // Get current working directory
    /*if (getcwd(buffer, sizeof(buffer)) != nullptr) {*/
    /*    std::cout << "Current working directory: " << buffer << std::endl;*/
    /*} else {*/
    /*    std::cerr << "Error: Unable to get the current working directory." << std::endl;*/
    /*}*/

    /*read(this->new_sock_fd,buffer,sizeof(buffer));*/
    /*std::cout<<buffer<<std::endl;*/
    std::cout<<"halo"<<endl;
    
    std::fstream f_obj;
    std::string file(buff);
    f_obj.open(file, std::ios::in);
    std::string file_lines;
    while(getline(f_obj, file_lines)){
        //sending all the lines in the file to the client.
        memset(buffer, '\0', sizeof(buffer));
        strcpy(buffer, file_lines.c_str());
        write(this->new_sock_fd, buffer, sizeof(buffer));
        /*std::cout<<buffer<<std::endl;*/
        /*std::cout<<"enters"<<std::endl;*/
    }
        /*std::cout<<"enters"<<std::endl;*/
    memset(&buffer, '\0', sizeof(buffer));
    strcpy(buffer, END_MESSAGE_CHARACTER);
    write(this->new_sock_fd, buffer, sizeof(buffer));//to tell the client that the file has ended
    f_obj.close();
  }


  void Server::show_directories_files(char* path){

    std::fstream f_obj;
    int i=0;
    char buffer[BUFF_LEN];

    DIR* dir;
    struct dirent* en;
    dir=opendir(path);
    while(i==0){
      if(dir==NULL){
        break;
      }
      while((en=readdir(dir))!=NULL){
        std::string std= en->d_name;
        memset(&buffer,'\0',sizeof(buffer));
        strcpy(buffer,std.c_str());
        if(sizeof(buffer)>3){
          /*cout<<buffer<<endl;*/
          write(this->new_sock_fd,buffer,sizeof(buffer));
        }
        //some random dots were appearing in output so tryin to remove them
      }

      memset(&buffer,'\0',sizeof(buffer));
      strcpy(buffer,END_MESSAGE_CHARACTER);
      write(this->new_sock_fd,buffer,sizeof(buffer));//to tell that the list of files is over
    }
    read(this->new_sock_fd,buffer,sizeof(buffer));
    closedir(dir);
    cout<<buffer<<endl;
    get_file_content(buffer);
  }


  unsigned char* Server::send_image(char* file_path) {
    show_directories_files(file_path);

    int width, height, channels;
    unsigned char* img = stbi_load(file_path, &width, &height, &channels, 0);
    if(img == NULL){
      printf("Error in loading the image \n");
      /*exit(1);*/
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

