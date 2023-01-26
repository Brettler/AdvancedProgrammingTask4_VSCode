// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandUploadCSV::CommandUploadCSV(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
    this -> description = "1. upload an unclassified csv data file\n";
}
CommandUploadCSV::~CommandUploadCSV() {}

// Upload the client file contents into a file on the server.
bool CommandUploadCSV::UploadFile(string FileCSV, string UploadMessage) {
    
    // Creating new file in the server to save the data contents.
    ofstream ServerDataFile(FileCSV);

    // Request a train set file from the client, and check with the client that the file is valid.
    dio -> write(UploadMessage);
    string row;
    row = dio -> read();
    if (row == "invalid input") {
             return false;
    }
    
    // Insert the client's file contents into the server's file, removing the empty row at the end.
    do {
        ServerDataFile << row << endl;
        row = dio -> read();
        if (row == "//EOM_MARKER") {
            ServerDataFile.close();
            ifstream ifs(FileCSV);                                  // Reading file contents.
            string content((istreambuf_iterator<char>(ifs)),
                        (istreambuf_iterator<char>()));             // Convert to string.            
            size_t last_line_break = content.find_last_of("\n");    // Search for last '\n'.
            content.erase(last_line_break, content.length());       // Delete last row (its empty).
            ofstream ofs(FileCSV);
            ofs << content;                                         // Remove the last line of the file which is empty.
            ofs.close();
        }
    } while (row != "//EOM_MARKER");
    return true;
}

// Check the train and test file paths and contents, and upload them into a file on the server.
void CommandUploadCSV::execute(SharedData* shared) {
  
    string TrainCSV = "Classy_" + to_string(shared -> CLISockNum) + "_" + to_string(shared -> counter) + ".csv";
    string UploadTrain = "Please upload your local train CSV file.\n";

    string TestCSV = "Unclassy_" + to_string(shared -> CLISockNum) + "_" + to_string(shared -> counter) + ".csv";
    string UploadTest = "Please upload your local test CSV file.\n ";
    
    // Validate the train file path.
    bool ValidPathTrain = UploadFile(TrainCSV, UploadTrain);
    if (!ValidPathTrain) {
        return;
    }

    // Set the classified file path and the DataImport object in the SharedData.
    shared -> SetClassifiedPath(TrainCSV);
    shared -> SetClassifiedData();

    // Validate the train file contents.
    bool ValidUploadClassified = shared -> GetClassifiedData() -> ReadClassifiedData();
    if (!ValidUploadClassified) {
        dio -> write("invalid input\n");
        return;
    } else {
        dio -> write("Upload complete.\n");
    }

    // Validate the test file path.
     bool ValidPathTest = UploadFile(TestCSV, UploadTest);
    if (!ValidPathTest) {
        return;
    }

    // Set the unclassified file path and the DataImport object in the SharedData.
    shared -> SetUnclassifiedPath(TestCSV);
    shared -> SetUnclassifiedData();

    // Validate the test file contents.
    bool ValidUploadUnclassified = shared -> GetUnclassifiedData() -> ReadUnclassifiedData(shared ->GetClassifiedData() -> GetDataMap());
    if (!ValidUploadUnclassified){
        dio -> write("invalid input\n");
        return;
    } else {
        dio -> write("Upload complete.\n");
    }

    // Little trick for naming files so we don't override the contents.
    shared -> counter++;
}

// Command description.
string CommandUploadCSV::GetDescription() {
    return this -> description;
}