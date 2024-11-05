#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main(){


    // Step 1: Syntax
    /*
        AF_INET: Specficies the IPv4 protocol family
        SOCK_STREAM: Specifies that we are using TCP instead of UDP (SOCK_DGRAM)
        0: Default Protocol

        Returns a sockfd: A file descriptor for the socket;
    */
    int serverSocket0 = socket(AF_INET, SOCK_STREAM, 0);
    // cout << serverSocket0 << endl; // Outputs 3 (?)

    int serverSocket1 = socket(AF_INET6, SOCK_STREAM, 0);
    // cout << serverSocket1 << endl; // Outputs 4


    // Step 2: Defining Server Address
    /*
        sockaddr_in: The data type that is used to store the address of the socket.
        htons(): This function is used to convert the unsigned int from machine byte order
                 to network byte order (endianness?)
        INADDR_ANYY: This is usedwhen we don't want to bind our socket to any particular IP 
                     and instead make it listen to all the available IPs

    */
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Binding the Server Socket
    bind(serverSocket0, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

    // Step 4: Listening for Connections
    listen(serverSocket0, 5);
    
    // Step 5: Accepting a Client Connection
    int clientSocket = accept(serverSocket0, nullptr, nullptr);

    // Step 6: recieving Data from the Client
    char buffer[1024] = {0};
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "Message from client: " << buffer << endl;

    // Step 6: Close Server Connection
    close(serverSocket0);


}