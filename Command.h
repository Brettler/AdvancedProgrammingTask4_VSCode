// Eden Berman 318530474
// Liad Brettler 318517182

#ifndef HEADER_COMMAND_H
#define HEADER_COMMAND_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
#include <ctime>
#include <mutex>
#include "DefaultIO.h"
#include "SharedData.h"
#include "DataImport.h"
#include "KNN.h"
using namespace std;

class Command {
protected:
    SharedData* shared;
    DefaultIO* dio;
    string description;
public:
    Command(DefaultIO* dio, SharedData* shared);
    virtual ~Command();
    virtual void execute(SharedData* shared) = 0;
    virtual string GetDescription() = 0;
};


// #1
class CommandUploadCSV : public Command {
public:
    explicit CommandUploadCSV(DefaultIO* dio, SharedData* shared);
    ~CommandUploadCSV();
    void execute(SharedData* shared) override;
    string GetDescription() override;
    bool UploadFile(string FileCSV, string UploadMessage);
};

// #2
class CommandSettingsKNN : public Command {
public:
    explicit CommandSettingsKNN(DefaultIO* dio, SharedData* shared);
    ~CommandSettingsKNN();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};

// #3
class CommandClassify : public Command {
public:
    explicit CommandClassify(DefaultIO* dio, SharedData* shared);
    ~CommandClassify();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};

// #4
class CommandDisplay : public Command {
public:
    explicit CommandDisplay(DefaultIO* dio, SharedData* shared);
    ~CommandDisplay();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};

// #5
class CommandDownload : public Command {
public:
    explicit CommandDownload(DefaultIO* dio, SharedData* shared);
    ~CommandDownload();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};

// #8
class CommandExit : public Command {
public:
    explicit CommandExit(DefaultIO* dio, SharedData* shared);
    ~CommandExit();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};

#endif //HEADER_COMMAND_H