#pragma once
#include "core.h"

namespace Client {

	extern sem_t x, y;
	extern pthread_t tid;
	extern pthread_t readerthreads[100];
	extern int readercount;


	void* reader(void* param);
	void* writer(void* param);

	class Client{
		public:
			Client()
				:sockfd(-1),
				port(8080)
		{
		}
			~Client(){
				close(sockfd);
			}

			void create_tcp_socket();
			void reuse_tcp_socket();
			void connect_tcp_socket(struct sockaddr_in& client,int port) ;
			void transfer_via_socket(char* buffer);
			void chat_to_server();

      void image_transfer(char* path);
			void get_file_names() const;
			unsigned char* send_image(char* file_path);
			bool write_image(char* img_data, char* path, int width, int height, int channels);
      void get_file_content() const;


		private:
			int sockfd;
			int port;
			struct sockaddr_in servaddr;
	};


}  // namespace Client
