// Eden Berman 318530474
// Liad Brettler 318517182

#include "CLI.h"
// Command line interface
CLI::CLI(DefaultIO* dio) {
    this->dio=dio;
    this -> shared = new SharedData;

    this -> CommandCSV = new CommandUploadCSV(dio, shared);
    CommandsVec.push_back(CommandCSV);

    this -> CommandKill = new CommandExit(dio, shared);
    CommandsVec.push_back(CommandKill);
    //commands.push_back(new Settings(dio));
    //commands.push_back(new Detect(dio));
    //commands.push_back(new Results(dio));
    //commands.push_back(new UploadAnom(dio));
    //commands.push_back(new Exit(dio));
}

void CLI::start(){
    int UserChoice=0;
    vector<int> ValidChoices = {1, 2, 3, 4, 5 ,8};
    while(UserChoice!=8){
        string WelcomeMenu = "Welcome to the KNN Classifier Server. Please choose an option:\n";
        dio -> write(WelcomeMenu);
        for (int i = 0; i < CommandsVec.size(); ++i) {
            dio -> write(CommandsVec[i]->GetDescription());
        }
        cout << "Server Waiting for user choise: " << endl;
        string ClientRespond = dio -> read();
        cout << "User Choise is: " << ClientRespond << endl;
        cout << "Now trying to conver choise to an int" << endl;
        UserChoice = atoi(ClientRespond.c_str());
        cout <<"Conver Success" << endl;
        if (count(ValidChoices.begin(), ValidChoices.end(), UserChoice) == 0) {
            dio -> write("Invalid Choose.\n") ;
            continue;
        }
        if(UserChoice == 1){
            CommandsVec.at(0) -> execute(this -> shared);
        }
        if(UserChoice == 2){
            CommandsVec.at(1) -> execute(this -> shared);
        }
        

        // if (UserChoice == 8) {
        //     CommandsVec.at(5) -> execute(this -> shared);
        // }
        // else{
        //     CommandsVec.at(UserChoice - 1) -> execute(this -> shared);    
        // }
        
    }
}

CLI::~CLI() {
    for(size_t i=0;i<CommandsVec.size();i++){
        delete CommandsVec[i];
    }
}