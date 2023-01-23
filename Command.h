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
#include "DefaultIO.h"
#include "SharedData.h"
#include "DataImport.h"
using namespace std;


class Command {
protected:
    SharedData* shared;
    DefaultIO* dio;
    string description;
public:
    //Command(DefaultIO* dio, string description, SharedData* shared);
    Command(DefaultIO* dio, SharedData* shared);
    virtual ~Command();
    virtual void execute(SharedData* shared) = 0;
    virtual string GetDescription() = 0;
    //virtual SharedData* GetSharedData();
};

class CommandUploadCSV : public Command {
public:
    explicit CommandUploadCSV(DefaultIO* dio, SharedData* shared);
    ~CommandUploadCSV();
    void execute(SharedData* shared) override;
    string GetDescription() override;
    bool UploadFile(string FileCSV, string UploadMessage);
};

class CommandSettingsKNN : public Command {
public:
    explicit CommandSettingsKNN(DefaultIO* dio, SharedData* shared);
    ~CommandSettingsKNN();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};


class CommandExit : public Command {
public:
    explicit CommandExit(DefaultIO* dio, SharedData* shared);
    ~CommandExit();
    void execute(SharedData* shared) override;
    string GetDescription() override;
};



#endif //HEADER_COMMAND_H
