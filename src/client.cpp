#include "../libs/Client.h"
/*#include "../libs/Server.h"*/

#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <netinet/in.h>
#endif
/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/

using namespace std;

int main() {
#ifdef _WIN32
    // Initialize Winsock
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }
#endif
    Client::Client* client = new Client::Client();
    struct sockaddr_in server_address; 
    int port = 14000; 

    client->create_tcp_socket();

    client->connect_tcp_socket(server_address, port);

    char buffer[] = "Hello from Client";

    client->get_file_names();


    return 0;
}

