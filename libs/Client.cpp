
#include "Client.h"
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fstream>
#include "../external/stb_image.h"
#include "../external/stb_image_write.h"
#include "Server.h"

namespace Client {

  sem_t x, y;
  pthread_t tid;
  pthread_t readerthreads[100];
  int readercount = 0;

    void Client::create_tcp_socket() {
        LOG_NETWORK("Creating TCP socket...");
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        
        if (this->sockfd < 0) {
            LOG_ERROR("Failed to create socket");
            return;
        }
        
        LOG_SUCCESS("TCP socket created successfully (fd: %d)", this->sockfd);
    }
  void Client::reuse_tcp_socket(){
  } 
    void Client::connect_tcp_socket(struct sockaddr_in& client, int port) {
        LOG_NETWORK("Connecting to server at port %d...", port);
        
        memset(&client, '\0', sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(port);
        client.sin_addr.s_addr = INADDR_ANY;
        this->port = port;

        if (connect(sockfd, (struct sockaddr*)&client, sizeof(client)) < 0) {
            LOG_ERROR("Failed to connect to server on port %d", port);
            return;
        }
        
        LOG_SUCCESS("Connection to server established successfully");
    }
    void Client::transfer_via_socket(char* buffer) {
        LOG_NETWORK("Transferring data via socket (fd: %d)...", this->sockfd);
        
        write(this->sockfd, buffer, strlen(buffer) + 1); 
        LOG_DEBUG("Data sent to server: %s", buffer);

        char message[255];
        memset(message, '\0', sizeof(message)); 

        read(this->sockfd, message, sizeof(message)); 
        LOG_SUCCESS("Received message: %s", message);
    }
    void Client::chat_to_server() {
        LOG_NETWORK("Starting chat with server...");
        char buffer[BUFF_LEN];
        
        memset(buffer, '\0', sizeof(buffer));
        
        ssize_t bytes_read = read(this->sockfd, buffer, sizeof(buffer));
        if (bytes_read < 0) {
            LOG_ERROR("Failed to read message from server");
            return;
        }

        LOG_SUCCESS("Message received from server: %s", buffer);
    }

    void Client::get_file_content(const char* buff) const {
        LOG_FILE("Retrieving file content for: %s", buff);
        
        char buffer[BUFF_LEN] = {0};
        std::string paths = DATA_PATH_CLIENT;
        paths += "_copy_";
        paths += buff;
        
        std::fstream file(paths.c_str(), std::ios::out | std::ios::app);
        if (!file.is_open()) {
            LOG_ERROR("Failed to open file for writing: %s", paths.c_str());
            return;
        }
        
        file.write("", 0);
        
        while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
            memset(buffer, '\0', sizeof(buffer));
            read(this->sockfd, buffer, sizeof(buffer));
            
            if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
                file << buffer << std::endl;
            }
        }
        
        file.close();
        LOG_SUCCESS("File transfer completed for: %s", buff);
    }

    void Client::get_file_names() const {
        LOG_FILE("Retrieving file names from server...");
        
        char buffer[BUFF_LEN] = {0};
        
        LOG_INFO("Available files on server:");
        while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
            memset(buffer, '\0', sizeof(buffer));
            read(this->sockfd, buffer, sizeof(buffer));
            
            if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
                LOG_INFO("  - %s", buffer);
            }
        }
        
        LOG_SUCCESS("File list received from server");
        
        std::string file;
        std::cout << "Enter the file name: ";
        std::cin >> file;
        
        LOG_NETWORK("Requesting file: %s", file.c_str());
        write(this->sockfd, file.c_str(), file.size());
        get_file_content(file.c_str());
    }

}
