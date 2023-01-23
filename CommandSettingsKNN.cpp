// Eden Berman 318530474
// Liad Brettler 318517182


#include "Command.h"


CommandSettingsKNN::CommandSettingsKNN(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "2. algorithm settings\n";
        }

CommandSettingsKNN::~CommandSettingsKNN(){}

/*string Command::GetDescription() {
    return this->description;
}*/
/*SharedData* Command::GetSharedData() {
    return this->shared;
}*/

void CommandSettingsKNN::execute(SharedData* shared) {
    InputCheck CheckObject;
    int k = shared -> GetK();
    string StringK = to_string(k);
    string metric = this -> shared -> GetMetric();
    // Send to the client the k
    dio -> write(StringK+'\n');
    // Send to the client the metric
    dio -> write(metric+'\n');
    // Recive arugments from client
    string InputSetting = dio -> read();
    cout << "ServerMteric user input is: " << InputSetting << endl;
    // if (InputSetting == "0 0"){
    //     // Returning to menu
    //     return;
    // }
    // Checking User's argument "<k> <metric>"
    

    istringstream is(InputSetting);
    is >> StringK;
    k = CheckObject.ValidKNumber(StringK);
    is >> metric;
    bool ValidMetric = CheckObject.ValidDistanceMetric(metric);
    bool ValidSizeK = true;
    try {
        cout << "Very long and lage shittt " << shared->GetClassifiedData()->GetDataMap().size() << endl;
        if(shared->GetClassifiedData()->GetDataMap().size() < k) {
            ValidSizeK = false;
            cout << "Flag status is: " << ValidSizeK << endl;
        }
    } catch (int& nullptr_ex) {
        cout << "WE ARE IN CATCH !!! \n";
        ValidSizeK = false;
    }

    if (!ValidMetric && (k == -1 || !ValidSizeK )) {
        dio -> write("invalid_k_metric\n");
        return;
    } else if(k == -1 || !ValidSizeK) {
        dio -> write("invalid_k\n");
        return;
    } else if(!ValidMetric) {
        dio -> write("invalid_metric\n");
        return;
    }
    // Else we are update the new k and metric values
    shared -> SetK(k);
    shared -> SetMetric(metric);
}

string CommandSettingsKNN::GetDescription() {
    return this -> description;
}