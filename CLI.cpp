// Eden Berman 318530474
// Liad Brettler 318517182

#include "CLI.h"

// Constructor:
CLI::CLI(DefaultIO* dio, int ClientSockNum) {
    // DefaultIO and SharedData objects to enable all commands to collaborate on the same instances.
    this -> dio = dio;
    this -> shared = new SharedData(ClientSockNum);

    // Filling the command vector with the action options.
    this -> CommandCSV = new CommandUploadCSV(dio, shared);
    CommandsVec.push_back(CommandCSV);
    this -> CommandSettings = new CommandSettingsKNN(dio, shared);
    CommandsVec.push_back(CommandSettings);
    this -> CommandRunKNN = new CommandClassify(dio, shared);
    CommandsVec.push_back(CommandRunKNN);
    this -> CommandDisRes = new CommandDisplay(dio, shared);
    CommandsVec.push_back(CommandDisRes);
    this -> CommandDownRes = new CommandDownload(dio, shared);
    CommandsVec.push_back(CommandDownRes);
    this -> CommandKill = new CommandExit(dio, shared);
    CommandsVec.push_back(CommandKill);
}

// Begin operating the CLI:
void CLI::start() {
    InputCheck ic;
    int UserChoise = 0;
    vector<int> ValidChoices = {1, 2, 3, 4, 5 ,8};

    // The client's function is based on the CLI instance's operation.
    while (UserChoise != 8) {
        string WelcomeMenu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        dio -> write(WelcomeMenu);
        for (int i = 0; i < CommandsVec.size(); ++i) {
            dio -> write(CommandsVec[i] -> GetDescription());
        }

        // If UserChoise is not a numeric value, the ValidKNumber method will return -1.
        string ClientRespond = dio -> read();
        UserChoise = ic.ValidKNumber(ClientRespond.c_str());
        if (count(ValidChoices.begin(), ValidChoices.end(), UserChoise) == 0) {
            dio -> write("invalid input\n") ;
            continue;
        }

        // Executing commands:
        // Command 8 exits the program, however it is the fifth element in the vector.
        if (UserChoise == 8) {
            CommandsVec.at(5) -> execute(this -> shared);
        } else {
            CommandsVec.at(UserChoise - 1) -> execute(this -> shared);    
        }
    }
}

// Destructor:
CLI::~CLI() {
    delete shared;
    for (size_t i = 0; i < CommandsVec.size(); i++) {
        delete CommandsVec[i];
    }
}