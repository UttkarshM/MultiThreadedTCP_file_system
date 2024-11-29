#include "../libs/Client.h"
/*#include "../libs/Server.h"*/
#include <netinet/in.h>
/*#define STB_IMAGE_WRITE_IMPLEMENTATION*/

using namespace std;

int main() {
    Client::Client* client = new Client::Client();  // Create client object
    struct sockaddr_in server_address;  // To hold server address details
    int port = 14000;  // Define the port for the connection

    client->create_tcp_socket();

    client->connect_tcp_socket(server_address, port);

    char buffer[] = "Hello from Client";

    /*client->transfer_via_socket(buffer);*/
    /*client->chat_to_server();*/
    client->get_file_names();
    
    /*client->get_file_content(buffer);*/

    return 0;
}

