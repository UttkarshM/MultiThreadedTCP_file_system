#pragma once
#include "core.h"
#include <iostream>

#ifdef _WIN32
    #include <filesystem>
#else
    #include <pthread.h>
    #include <unistd.h>
    #include <dirent.h>
    #include <semaphore.h>
#endif

namespace Server {
    extern int top;
    extern int rear;
    extern int thread_no;
#ifdef _WIN32
    extern std::counting_semaphore<1024> x, y;
    extern std::thread tid;
    extern std::thread readerthreads[100];
#else
    extern sem_t x, y;
    extern pthread_t tid;
    extern pthread_t readerthreads[100];
#endif
    extern int readercount;
    extern int queue[1024 * 1024];

    void server_queue_pop();
    void server_queue_push(void* function(void*));

    class Server {
    public:
			Server()
				:sockfd(-1),new_sock_fd(-1),port(8080)
			{
			}
			~Server(){
				close(sockfd);
				close(new_sock_fd);
			}
        
        void create_tcp_socket();
        void reuse_tcp_socket();
        void bind_tcp_socket(struct sockaddr_in& server, int port);
        void listen_tcp_socket() const;
        void* accept_tcp();
        void return_ptr(void* arg);
        void connect_tcp_socket() const;
        void transfer_via_socket(char* buffer);

        void show_directories_files(char* path);
        void chat_to_client(int id);
        void get_file_names(char* buff) const;
        unsigned char* send_image(char* file_path);
        bool write_image(char* img_data, char* path, int width, int height, int channels);
        void get_file_content(char* buffer) const;

    private:
        int sockfd, new_sock_fd;
        int port;
        struct sockaddr_in servaddr;
    };
}

