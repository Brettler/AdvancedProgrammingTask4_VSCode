// Eden Berman 318530474
// Liad Brettler 318517182

#ifndef ADVANCEDPROGRAMMINGTASK3_SERVERCLASS_H
#define ADVANCEDPROGRAMMINGTASK3_SERVERCLASS_H
#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <cctype>
#include <utility>

#include "InputCheck.h"
#include "DefaultIO.h"
#include "CLI.h"


using namespace std;

class ServerClass {
private:
    // Port number.
    const int ServerPort;
    // DataMap will initialize when we create the ServerClass object.
    //const map<vector<double>, string>& DataMap;

public:
    // Constructor:
    ServerClass(int ServerPort);
    // Functions:
    void run() const;
    string CreatResponseMessage(string ServerResponseMessage, char buffer[]) const;
};
#endif //ADVANCEDPROGRAMMINGTASK3_SERVERCLASS_H
