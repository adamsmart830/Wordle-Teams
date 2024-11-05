#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

void sendMessage(int socket, string message){
    if(send(socket, message.c_str(), message.length(), 0) < 0){
        cerr << "Failed to send message" << endl;
    }
}

void checkAccept(int socket){
    if(socket < 0){
        cerr << "Failed to accept connection" << endl;
    }else{
        cout << "Connected to Socket #" << socket << endl;
    }
}

void checkServerSocket(int socket){
    if(socket < 0){
        cerr << "Failed to create socket" << endl;
    }
}




int main(){

    // Open Socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    checkServerSocket(serverSocket);

    // Socket Descriptors
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0){
        cerr << "Failed to bind socket" << endl;
        close(serverSocket);
        return -1;
    }

    if(listen(serverSocket, 2) < 0){
        cerr << "Failed to listen on socket" << endl;
        close(serverSocket);
        return -1;
    }

    cout << "Server is listening on port 8080..." << endl;


    // Accept 1st Client Connection
    int clientSocketA = accept(serverSocket, nullptr, nullptr);
    checkAccept(clientSocketA);
    

    // Alert Client 1 to wait for second connection
    string message = "Waiting for second connection...\n";
    sendMessage(clientSocketA, message);

    // Accept 2nd Client Connection
    int clientSocketB = accept(serverSocket, nullptr, nullptr);
    checkAccept(clientSocketB);

    // Alert Client 1 that second connection was successful;
    sendMessage(clientSocketA, "Second connection successful!\n");

    // Alert Client 2 that connection has been made
    sendMessage(clientSocketB, "Both Connections Successful\n");

    char buffer[1024] = {0};
    ssize_t bytesRead = recv(clientSocketA, buffer, sizeof(buffer), 0);

    if(bytesRead > 0){
        cout << "Message Recieved from client #" << clientSocketA << " " << buffer << endl;
    }else{
        cerr << "Failed to recieve message from client" << endl;
    }

    close(clientSocketA);


    close(serverSocket);
    return 0;



}