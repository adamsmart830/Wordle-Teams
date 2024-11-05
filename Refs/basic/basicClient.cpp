#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(){

    // Step 1: Creating the Client Socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);


    // Step 2: Defining the Client Socket
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Connecting to the Server
    connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Step 4: Sending Data to the server
    const char* message = "Hello Server!";
    send(clientSocket, message, strlen(message), 0);

    //Step 5: Close the Client Socket
    close(clientSocket);

}