// Eden Berman 318530474
// Liad Brettler 318517182

#include "DefaultIO.h"

SocketIO::SocketIO(int ClientSocket):ClientSocket(ClientSocket){}
SocketIO::~SocketIO(){}

// Reading from socket
 string SocketIO::read(){
    //cout << "Using Read function from SocketIO" << endl;
    string ServerMessage;
    char c = 0;
    // Reads the first character from the socket
    ::read(ClientSocket, &c, sizeof(char));
    //cout << c << endl;
    while (c != '\n') {
        //cout << "We are in the while loop reading : " << c << endl;
        ServerMessage += c;
        ::read(ClientSocket, &c, sizeof(char));
    }
    cout << "SocketIO::read() return: " << ServerMessage << endl;
    return ServerMessage;
}

// Write message through the socket connection
 void SocketIO::write(string information){
    cout << "Using SocketIO::write with the string: " << information << endl;
    ::write(ClientSocket, information.c_str(), information.length());
    //::write(ClientSocket, "\n", 1);
 }

 //void SocketIO::write(float f){};
 //void SocketIO::read(float* f){};