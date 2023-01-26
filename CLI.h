// Eden Berman 318530474
// Liad Brettler 318517182

#pragma once
#ifndef HEADER_CLI_H
#define HEADER_CLI_H

#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include "DefaultIO.h"
#include "SharedData.h"
#include "Command.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    SharedData* shared;
    CommandUploadCSV* CommandCSV;
    CommandSettingsKNN* CommandSettings;
    CommandClassify* CommandRunKNN;
    CommandDisplay* CommandDisRes;
    CommandDownload* CommandDownRes;
    CommandExit* CommandKill;
    vector<Command*> CommandsVec;
public:
    CLI(DefaultIO* dio, int ClientSockNum);
    void start();
    virtual ~CLI();
};
#endif //ADVANCEDPROGRAMMINGTASK4_CLI_H