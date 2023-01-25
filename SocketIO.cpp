// Eden Berman 318530474
// Liad Brettler 318517182

#include "DefaultIO.h"

SocketIO::SocketIO(int ClientSocket):ClientSocket(ClientSocket){}
SocketIO::~SocketIO(){}

// Reading from socket
 string SocketIO::read(){
    string ServerMessage;
    char c = 0;
    // Reads the first character from the socket
    ::read(ClientSocket, &c, sizeof(char));
    while (c != '\n') {
        // Adding each character to the output string.
        ServerMessage += c;
        ::read(ClientSocket, &c, sizeof(char));
    }
    //cout << "reading the messege: " << ServerMessage << endl;
    return ServerMessage;
}

// Write message through the socket connection
 void SocketIO::write(string information){
    ::write(ClientSocket, information.c_str(), information.length());
    //cout << "wrote the messege: " << information << endl;
 }
