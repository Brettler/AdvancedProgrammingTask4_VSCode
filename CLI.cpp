// Eden Berman 318530474
// Liad Brettler 318517182

#include "CLI.h"
// Command line interface
CLI::CLI(DefaultIO* dio, int ClientSockNum) {
    this->dio=dio;
    this -> shared = new SharedData(ClientSockNum);

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

void CLI::start(){
    InputCheck ic;
    int UserChoice=0;
    vector<int> ValidChoices = {1, 2, 3, 4, 5 ,8};
    while(UserChoice!=8){
        string WelcomeMenu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        dio -> write(WelcomeMenu);
        for (int i = 0; i < CommandsVec.size(); ++i) {
            dio -> write(CommandsVec[i]->GetDescription());
        }
  
        string ClientRespond = dio -> read();

        //UserChoice = atoi(ClientRespond.c_str());
        UserChoice = ic.ValidKNumber(ClientRespond.c_str());
        // if UserChoise is not numeric number ValidKNumber will return -1.
        if (count(ValidChoices.begin(), ValidChoices.end(), UserChoice) == 0) {
            dio -> write("invalid input\n") ;
            continue;
        }

        if (UserChoice == 8) {
            CommandsVec.at(5) -> execute(this -> shared);
        }
        else{
            CommandsVec.at(UserChoice - 1) -> execute(this -> shared);    
        }
        
    }
}

CLI::~CLI() {
    delete shared;
    for(size_t i=0;i<CommandsVec.size();i++){
        delete CommandsVec[i];
    }
}