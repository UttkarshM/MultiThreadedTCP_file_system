/*#pragma once*/
/*#include "core.h"*/
/*#include <iostream>*/
/*#include <pthread.h>*/
/*#include <unistd.h>*/
/*#include <dirent.h>*/
/**/
/*namespace Server {*/
/*	extern int top;*/
/*	extern int rear;*/
/*	extern int thread_no;*/
/*	extern sem_t x, y;*/
/*	extern pthread_t tid;*/
/*	extern pthread_t readerthreads[100];*/
/*	extern int readercount;*/
/*	extern int queue[1024*1024]; //apparently the hard limit*/
/*	void* reader(void* param);*/
/*	void* writer(void* param);*/
/**/
/*	class Server{*/
/*		private:*/
/*		public:*/
			/*Server()*/
			/*	:sockfd(-1),new_sock_fd(-1),port(8080)*/
			/*{*/
			/*}*/
			/*~Server(){*/
			/*	close(sockfd);*/
			/*	close(new_sock_fd);*/
			/*}*/
/*			void create_tcp_socket();*/
/*			void reuse_tcp_socket();*/
/*			void bind_tcp_socket(struct sockaddr_in& server,int port);*/
/*			void listen_tcp_socket() const;*/
/*			void* accept_tcp();*/
/*			void return_ptr(void* arg);*/
/*			void connect_tcp_socket() const ;*/
/*			void transfer_via_socket(char* buffer);*/
/**/
/*			//un*/
/*			void show_directories_files(char* path);*/
/*			void chat_to_client(int id);*/
/*			void get_file_names(char* buff) const;*/
/*			unsigned char* send_image(char* file_path);*/
/*			bool write_image(char* img_data, char* path, int width, int height, int channels);*/
/*      void get_file_content(char* buffer) const;*/
/*		private:*/
/*			int sockfd,new_sock_fd;*/
/*			int port;*/
/*			struct sockaddr_in servaddr;*/
/*	};*/
/**/
/*	void server_queue_pop(){*/
/*		pthread_join(readerthreads[++rear],NULL);*/
/*	}*/
/* void server_queue_push(void* function(void*)){*/
/*		pthread_create(&readerthreads[++top],NULL,function,NULL);*/
/*		server_queue_pop();*/
/*	}*/
/*}*/


#pragma once
#include "core.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <semaphore.h>

namespace Server {
    // Global variables
    extern int top;
    extern int rear;
    extern int thread_no;
    extern sem_t x, y;
    extern pthread_t tid;
    extern pthread_t readerthreads[100];
    extern int readercount;
    extern int queue[1024 * 1024];

    // Queue management
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
        
        // Core TCP functionality
        void create_tcp_socket();
        void reuse_tcp_socket();
        void bind_tcp_socket(struct sockaddr_in& server, int port);
        void listen_tcp_socket() const;
        void* accept_tcp();
        void return_ptr(void* arg);
        void connect_tcp_socket() const;
        void transfer_via_socket(char* buffer);

        // Utilities
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

