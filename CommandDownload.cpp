// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandDownload::CommandDownload(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "5. download results\n";
        }
CommandDownload::~CommandDownload() {}

// Download the classification results into a file locally.
void CommandDownload::execute(SharedData* shared) {
    // If the data has yet to be uploaded or classified, return.
    if (shared -> ClassifiedData == nullptr) {
        dio -> write("please upload data\n");
        return;
    }
    if ((*shared -> GetResultsVector()).size() == 0) {
        dio -> write("please classify the data\n");
        return;
    }
    dio -> write("good\n");

    // If the server received the message 'err_exp', than the user input an invalid path.
    // Otherwise the server received the message 'good', so the downloading operation can take place.
    string check = dio -> read();
    if (check == "err_exp") {
        return;
    }
 
    string index;
    // Insert the classification results into a file in the following format: <index> <label>.
    for (int i = 0; i < (*shared -> GetResultsVector()).size(); i++) {
        index = to_string(i + 1);
        dio -> write(index + "   " + (*shared -> GetResultsVector()).at(i) + "\n");
    }
    dio -> write("Done.\n");
}

// Command description.
string CommandDownload::GetDescription() {
    return this -> description;
}