// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

CommandUploadCSV::CommandUploadCSV(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared){
    this -> description = "1. upload an unclassified csv data file\n";
}
CommandUploadCSV::~CommandUploadCSV(){}

bool CommandUploadCSV::UploadFile(string FileCSV, string UploadMessage){
    // Creating new file to save in the server
    ofstream ServerDataFile(FileCSV);
    // Send to the Client what file the user need to give
    dio->write(UploadMessage);
    string row;
    row = dio -> read();
    if (row == "invalid input") {
             //cout << "Return false because of row is invalid" << endl;
             return false;
    }
    
    do{
        ServerDataFile << row << endl;
        row = dio -> read();
        // We clean the whitspace in the last row
        if (row == "//EOM_MARKER") {
            //cout << "we need to delete the last empty row\n";
            ServerDataFile.close();
            // reading the content of the file to ifs object 
            ifstream ifs(FileCSV);
            // reading the content of the file into a string
            string content((istreambuf_iterator<char>(ifs)), 
                        (istreambuf_iterator<char>()));
            // Searching the last row (last \n).            
            size_t last_line_break = content.find_last_of("\n");
            // Delte the content of the last row (everything after the last '/n')
            content.erase(last_line_break, content.length());
            // Creating ofs Object again
            ofstream ofs(FileCSV);
            // Changing the content of the file saved in the server to be without the last empty row
            ofs << content;
            ofs.close();
        }
    } while (row != "//EOM_MARKER");
    return true;
}



void CommandUploadCSV::execute(SharedData* shared) {
  
    string TrainCSV = "Classy_" + to_string(shared -> CLISockNum) +"_"+ to_string(shared->counter) + ".csv";
    string UploadTrain = "Please upload your local train CSV file.\n";

    string TestCSV = "Unclassy_" + to_string(shared -> CLISockNum) +"_"+ to_string(shared->counter) + ".csv";
    string UploadTest = "Please upload your local test CSV file.\n ";
    
    // Training set proccess:
    bool ValidPathTrain = UploadFile(TrainCSV, UploadTrain);
    if (!ValidPathTrain) {
        return;
    }

    shared -> SetClassifiedPath(TrainCSV);
    // Cread DataImport Object with the corrent path;
    shared -> SetClassifiedData();
    // Creat the classified map.
    bool ValidUploadClassified = shared -> GetClassifiedData() -> ReadClassifiedData();

    if (!ValidUploadClassified){
        dio -> write("invalid input\n");
        return;
    } else {
        dio -> write("Upload complete.\n");
    }

    // Test set proccess:
     bool ValidPathTest = UploadFile(TestCSV, UploadTest);
    if (!ValidPathTest) {
        return;
    }

    shared -> SetUnclassifiedPath(TestCSV);
    // Cread DataImport Object with the corrent path;
    shared -> SetUnclassifiedData();
    bool ValidUploadUnclassified = shared -> GetUnclassifiedData() -> ReadUnclassifiedData(shared ->GetClassifiedData() -> GetDataMap());
    if (!ValidUploadUnclassified){
        dio -> write("invalid input\n");
        return;
    } else {
        dio -> write("Upload complete.\n");
    }
    shared->counter++;
}

string CommandUploadCSV::GetDescription() {
    return this->description;
}