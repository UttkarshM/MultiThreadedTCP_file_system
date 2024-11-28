
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
    
    /*std::cout << "Enter the message to be sent\n";*/
    /*std::cin.getline(buffer, sizeof(buffer));*/
    /**/
    /*ssize_t bytes_written = write(this->sockfd, buffer, strlen(buffer) + 1);*/
    /*if (bytes_written < 0) {*/
    /*    std::cerr << "Failed to send message to server" << std::endl;*/
    /*    return;*/
    /*}*/
    
    memset(buffer, '\0', sizeof(buffer));
    
    ssize_t bytes_read = read(this->sockfd, buffer, sizeof(buffer));
    if (bytes_read < 0) {
        std::cerr << "Failed to read message from server" << std::endl;
        return;
    }

    std::cout << "Message received from server: " << buffer << "\n";
}

void Client::get_file_content(char* buff) const{
    /*std::fstream f_obj;*/
    /*char buffer[BUFF_LEN];*/
    /*std::string file(buff);*/
    /*f_obj.open(file,std::ios::in);*/
    /*std::string file_lines;*/
    /*while(getline(f_obj,file_lines)){*/
    /*    //sending all the lines in the file to the client.*/
    /*    memset(buffer,'\0',sizeof(buffer));*/
    /*    strcpy(buffer,file_lines.c_str());*/
    /*    write(this->sockfd,buffer,sizeof(buffer));*/
    /*}*/
    /*memset(&buffer,'\0',sizeof(buffer));*/
    /*strcpy(buffer,END_MESSAGE_CHARACTER);*/
    /*write(this->sockfd,buffer,sizeof(buffer));//to tell the client that the file has ended*/
    /*f_obj.close();*/
    char buffer[BUFF_LEN]="hello";
    /*std::cout<<buffer<<std::endl;*/
    while(strcmp(buffer,END_MESSAGE_CHARACTER) != 0){
      /*std::cout<<"Hello"<<std::endl;*/
      memset(buffer, '\0', sizeof(buffer));
      read(this->sockfd, buffer, sizeof(buffer));
      if(strlen(buffer)>0 && buffer[0]!='.' && strcmp(buffer,END_MESSAGE_CHARACTER)!=0){//filter out the hidden files
        std::cout << buffer << "\n";
      }
    }
    sleep(10);

}

  void Client::get_file_names(char* buff) const {
    char buffer[BUFF_LEN];
    while(strcmp(buffer,END_MESSAGE_CHARACTER) != 0){
      memset(buffer, '\0', sizeof(buffer));
      read(this->sockfd, buffer, sizeof(buffer));
      if(strlen(buffer)>0 && buffer[0]!='.' && strcmp(buffer,END_MESSAGE_CHARACTER)!=0){//filter out the hidden files
        std::cout << buffer << "\n";
      }
    }
    std::cout<<"File received"<<std::endl;
    std::string file;
    std::cout<<"Enter the file name"<<std::endl;
    std::cin>>file;
    write(this->sockfd,file.c_str(),file.size());
    get_file_content(buffer);//re,pve the variable we dont use it
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
