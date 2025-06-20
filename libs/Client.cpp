#include "Client.h"
#include "Server.h"
#include <iostream>
#include <fstream>
#include <string.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <semaphore>
#else
    #include <netinet/in.h>
    #include <unistd.h>
    #include <semaphore.h>
#endif

#include "../external/stb_image.h"
#include "../external/stb_image_write.h"

// #define STB_IMAGE_WRITE_IMPLEMENTATION

namespace Client {

#ifdef _WIN32
    std::counting_semaphore<1024> x(1), y(1);
    std::thread tid;
    std::thread readerthreads[100];
#else
    sem_t x, y;
    pthread_t tid;
    pthread_t readerthreads[100];
#endif

    int readercount = 0;


    void Client::create_tcp_socket() {
        this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (this->sockfd < 0) {
            logger("socket");
        }
        std::cout << "Socket created successfully.\n";
    }

    void Client::reuse_tcp_socket() {
    }

    void Client::connect_tcp_socket(struct sockaddr_in& client, int port) {
        memset(&client, '\0', sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(port);
        client.sin_addr.s_addr = INADDR_ANY;
        this->port = port;

        if (connect(sockfd, (struct sockaddr*)&client, sizeof(client)) < 0) {
            logger("connecting");
        }

        std::cout << "Connection has been established successfully.\n";
    }


    void Client::transfer_via_socket(char* buffer) {
        std::cout << this->sockfd << std::endl;

#ifdef _WIN32
        socket_write(this->sockfd, buffer, strlen(buffer) + 1);
#else
        write(this->sockfd, buffer, strlen(buffer) + 1);
#endif

        char message[255] = {0};

#ifdef _WIN32
        socket_read(this->sockfd, message, sizeof(message));
#else
        read(this->sockfd, message, sizeof(message));
#endif

        std::cout << "Received message: " << message << "\n";
    }

    void Client::chat_to_server() {
        char buffer[BUFF_LEN] = {0};

#ifdef _WIN32
        ssize_t bytes_read = socket_read(this->sockfd, buffer, sizeof(buffer));
#else
        ssize_t bytes_read = read(this->sockfd, buffer, sizeof(buffer));
#endif

        if (bytes_read < 0) {
            std::cerr << "Failed to read message from server.\n";
            return;
        }

        std::cout << "Message received from server: " << buffer << "\n";
    }

    void Client::get_file_names() const {
        char buffer[BUFF_LEN] = {0};

        // Receive list of file names
        while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
            memset(buffer, '\0', sizeof(buffer));

#ifdef _WIN32
            socket_read(this->sockfd, buffer, sizeof(buffer));
#else
            read(this->sockfd, buffer, sizeof(buffer));
#endif

            if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
                std::cout << buffer << "\n";
            }
        }

        std::string file;
        std::cout << "Enter the file name: ";
        std::cin >> file;

#ifdef _WIN32
        socket_write(this->sockfd, file.c_str(), file.size());
#else
        write(this->sockfd, file.c_str(), file.size());
#endif

        get_file_content(file.c_str());
    }

    void Client::get_file_content(const char* buff) const {
        char buffer[BUFF_LEN] = {0};
        std::string paths = DATA_PATH_CLIENT + std::string("_copy_") + buff;

        std::ofstream file(paths, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << paths << std::endl;
            return;
        }

        while (strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
            memset(buffer, '\0', sizeof(buffer));

#ifdef _WIN32
            socket_read(this->sockfd, buffer, sizeof(buffer));
#else
            read(this->sockfd, buffer, sizeof(buffer));
#endif

            if (strlen(buffer) > 0 && buffer[0] != '.' && strcmp(buffer, END_MESSAGE_CHARACTER) != 0) {
                file.write(buffer, strlen(buffer));
                file.write("\n", 1);
            }
        }

        file.close();
        std::cout << "File transfer completed.\n";
    }


    unsigned char* Client::send_image(char* file_path) {
        int width, height, channels;
        unsigned char* img = stbi_load(file_path, &width, &height, &channels, 0);

        if (img == nullptr) {
            std::cerr << "Error in loading the image.\n";
            return nullptr;
        }

        stbi_image_free(img);
        return img;
    }

    bool Client::write_image(char* img_data, char* path, int width, int height, int channels) {
        stbi_write_png(path, width, height, channels, img_data, width * channels);
        return true;
    }

}
