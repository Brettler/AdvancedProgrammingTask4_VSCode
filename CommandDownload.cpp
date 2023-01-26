// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"
// ---------------------------------------------------------------------------------------------------------------------------
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

    // if server read err_exp means the user gave invalid path.
    // else the server will read "good" and we continue with the download
    //cout << "before reading response from the server\n";
    if (dio -> read() == "err_exp") {
        return;
    }
    // else {
    //     dio -> read(); // reading "good" response from the server.
    // }
    string index;
    // Insert the classification results into a file in the following format: <index> <label>.
    for (int i=0; i < (*shared -> GetResultsVector()).size(); i++) {
        index = to_string(i + 1);
        //cout << "write the inforamtion in the row that needed to be writen in the file\n";
        dio -> write(index + "   " + (*shared -> GetResultsVector()).at(i) + "\n");
    }
    dio -> write("Done.\n");
}

// Command description.
string CommandDownload::GetDescription() {
    return this -> description;
}