// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

/*UploadCSV::UploadCSV(DefaultIO* dio, SharedData* SharedInfo)
:Command(dio,"1. upload an unclassified csv data file", SharedInfo){};*/

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

    bool FlagEOM = false;
    string row = "0";
    while (!FlagEOM) {
        row = dio -> read();
        cout << "Row is: " << row << endl;
        if (row == "//EOM_MARKER") {
            FlagEOM = true;
            cout << "we need to delete the last empty row\n";
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
        else{
            ServerDataFile << row << endl;    
        }
 
    }
    // DataImport data(FileCSV);
    // cout << "FileCSV is: " << FileCSV << endl;
    // if (FileCSV == "ClassifiedFileServer.csv"){
    //     if(!data.ReadClassifiedData()){
    //         dio -> write("invalid input\n");
    //         return false;
    //     }
    // }
    // cout << "FileCSV is: " << FileCSV << endl;
    // if(FileCSV == "UnclassifiedFileServer.csv"){
    //     if(!data.ReadUnclassifiedData()){
    //         dio -> write("invalid input\n");
    //         return false;
    //     }
    // }
    // //cout << "Server is need to write upload complete" << endl;
    // dio -> write("Upload complete.\n");
    // //ServerDataFile.close();
    // return true;
}



void CommandUploadCSV::execute(SharedData* shared) {

    string TrainCSV = "ClassifiedFileServer.csv";
    string UploadTrain = "Please upload your local train CSV file.\n";

    string TestCSV = "UnclassifiedFileServer.csv";
    string UploadTest = "Please upload your local test CSV file.\n ";
 
    // Training set proccess:
    UploadFile(TrainCSV, UploadTrain);

    shared -> SetClassifiedPath(TrainCSV);

    bool ValidUploadClassified = shared -> GetClassifiedData() -> ReadClassifiedData();

    if (!ValidUploadClassified){
        dio -> write("invalid input\n");
        return;
    }

    // Test set proccess:
    UploadFile(TestCSV, UploadTest);

    shared -> SetUnclassifiedPath(TestCSV);

    bool ValidUploadUnclassified = shared -> GetUnclassifiedData() -> ReadUnclassifiedData();

    if (!ValidUploadUnclassified){
        dio -> write("invalid input\n");
        return;
    }
}

string CommandUploadCSV::GetDescription() {
    return this->description;
}