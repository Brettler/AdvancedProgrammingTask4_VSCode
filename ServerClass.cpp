// Eden Berman 318530474
// Liad Brettler 318517182

#include "ServerClass.h"

// Constructor
ServerClass::ServerClass(int ServerPort):ServerPort(ServerPort)  {
    // Initialize a socket.
    this -> sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
    }
    // Configure the IP address and port.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(ServerPort);

    // Bind the socket to the IP address and port.
    if (bind(sock,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }
}

void ServerClass::run() {
    // Listen for incoming connections. Up to five clients at a time.
    while(true) {
        if (listen(sock, 5) < 0) {
            perror("error listening to a socket");
            exit(1);
        }
        // Accept connection from a client.
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int ClientSock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (ClientSock < 0) {
            perror("error accepting client");
            exit(1);
        }

        ClientQueue.push(ClientSock);
        // Creat new thread
        ThreadPool.emplace_back(&ServerClass::ThreadExecutor, this);

    }
}

void ServerClass::ThreadExecutor() {
    while (true) {
        int ClientSock = ClientQueue.front();
        ClientQueue.pop();
        SocketIO SockOBJ(ClientSock);
        CLI cli(&SockOBJ, ClientSock);
        cli.start();
    }
}