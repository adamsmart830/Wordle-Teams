#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

int main(){

    // Step 1: Creating the Client Socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(clientSocket < 0){
        cerr << "Failed to create socket" << endl;
        return -1;
    }


    // Step 2: Defining the Client Socket
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Step 3: Connecting to the Server
    if(connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        cerr << "Server connection Failed" << endl;
        close(clientSocket);
        return -1;
    }

    char buffer[1024] = {0};
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if(bytesRead > 0){
        cout << buffer;
    }

    // Step 4: Sending Data to the server
    string message;
    cout << "Enter a message to send to the server" << endl;
    getline(cin, message);
    if(send(clientSocket, message.c_str(), message.length(), 0) < 0){
        cerr << "Failed to send message" << endl;
    }
    
    //Step 5: Close the Client Socket
    close(clientSocket);
    return 0;

}