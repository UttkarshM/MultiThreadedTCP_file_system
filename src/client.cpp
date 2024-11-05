#include "../libs/Client.cpp"
/*#include "../libs/Server.h"*/
#include <netinet/in.h>

using namespace std;

int main() {
    Client::Client* client = new Client::Client();  // Create client object
    struct sockaddr_in server_address;  // To hold server address details
    int port = 14000;  // Define the port for the connection

    // Create a TCP socket for the client
    client->create_tcp_socket();

    // Connect the client to the server on the specified port
    client->connect_tcp_socket(server_address, port);

    // Prepare the buffer with some message to send to the server
    char buffer[] = "Hello from Client";

    // Send the message to the server
    client->transfer_via_socket(buffer);

    // After sending, client will wait for the server response and print it
    // (this happens inside the transfer_via_socket method)

    // End the client program
    return 0;
}

