// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandDisplay::CommandDisplay(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "4. display results\n";
        }
CommandDisplay::~CommandDisplay() {}

// Display the classification results to the user.
void CommandDisplay::execute(SharedData* shared) {
    string index;

    // If the data has yet to be uploaded or classified, return.
    if (shared -> ClassifiedData == nullptr) {
        dio -> write("please upload data\n");
        return;
    }
    if ((*shared -> GetResultsVector()).size() == 0) {
        dio -> write("please classify the data\n");
        return;
    }

    // Display the classification results in the following format: <index> <label>.
    for (int i = 0; i < (*shared -> GetResultsVector()).size(); i++) {
        index = to_string(i + 1);
        dio -> write(index + "   " + (*shared -> GetResultsVector()).at(i) + "\n");
    }
     dio -> write("Done.\n");
}

// Command description.
string CommandDisplay::GetDescription() {
    return this -> description;
}