// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandSettingsKNN::CommandSettingsKNN(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "2. algorithm settings\n";
        }
CommandSettingsKNN::~CommandSettingsKNN() {}

// Set the K and metric values.
void CommandSettingsKNN::execute(SharedData* shared) {
    InputCheck CheckObject;
    int k = shared -> GetK();
    string StringK = to_string(k);
    string metric = this -> shared -> GetMetric();

    // Send the client the current K and metric values.
    dio -> write(StringK + '\n');
    dio -> write(metric + '\n');

    // Recive arugments from the client.
    string InputSetting = dio -> read();
  
    // Separate the string into two corresponding arguments.
    istringstream is(InputSetting);
    is >> StringK;
    k = CheckObject.ValidKNumber(StringK);
    is >> metric;
    bool ValidMetric = CheckObject.ValidDistanceMetric(metric);
    bool ValidSizeK = true;

    // If the data has yet to be uploaded, a K value can't be chosen.
    if (shared -> ClassifiedData == nullptr) {
        ValidSizeK = false;
    }

    // Validate the K and metric values.
    if (!ValidMetric && (k == -1 || !ValidSizeK )) {
        dio -> write("invalid_k_metric\n");
        return;
    } else if (k == -1 || !ValidSizeK) {
        dio -> write("invalid_k\n");
        return;
    } else if (!ValidMetric) {
        dio -> write("invalid_metric\n");
        return;
    }

    // Update the K and metric values.
    shared -> SetK(k);
    shared -> SetMetric(metric);
}

// Command Description.
string CommandSettingsKNN::GetDescription() {
    return this -> description;
}