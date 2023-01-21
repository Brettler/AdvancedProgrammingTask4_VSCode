// Eden Berman 318530474
// Liad Brettler 318517182

#ifndef ADVANCEDPROGRAMMINGTASK4_DEFAULTIO_H
#define ADVANCEDPROGRAMMINGTASK4_DEFAULTIO_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
using namespace std;

class DefaultIO {
protected:
    ofstream output;
    ifstream input;
public:
    virtual string read()=0;
    virtual void write(string text)=0;
    virtual void write(float f)=0;
    virtual void read(float* f)=0;

    virtual ~DefaultIO();
};

class SocketIO: public DefaultIO{
    int ClientSocket;
public:

    explicit SocketIO(int ClientID);

    string read() override;
    void write(string information) override;

    void write(float f) override;

    void read(float* f) override;

};
#endif //ADVANCEDPROGRAMMINGTASK4_DEFAULTIO_H
