// Eden Berman 318530474
// Liad Brettler 318517182

#include "CLI.h"
// Command line interface
CLI::CLI(DefaultIO *dio) {
    this->dio=dio;
    this -> shared = new SharedData;

    this -> CommandCSV = new CommandUploadCSV(dio, shared);
    CommandsVec.push_back(CommandCSV);

    //commands.push_back(new Settings(dio));
    //commands.push_back(new Detect(dio));
    //commands.push_back(new Results(dio));
    //commands.push_back(new UploadAnom(dio));
    //commands.push_back(new Exit(dio));
}

void CLI::start(){
    int UserChoice=0;
    while(UserChoice!=6){
        string WelcomeMenu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        dio -> write(WelcomeMenu);
        for (int i = 0; i < CommandsVec.size(); ++i) {
            dio -> write(CommandsVec[i]->GetDescription());
        }
        UserChoice = atoi(dio -> read().c_str());
        if (UserChoice < 1 || UserChoice > 6) {
            dio -> write("Invalid Choose.") ;
            continue;
        }
        CommandsVec.at(UserChoice - 1) -> execute(this -> shared);
    }
}

CLI::~CLI() {
    for(size_t i=0;i<CommandsVec.size();i++){
        delete CommandsVec[i];
    }
}