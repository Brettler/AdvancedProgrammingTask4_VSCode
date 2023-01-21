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



void CommandUploadCSV::UploadFile(string FileCSV, string UploadMessage){
    // Creating new file to save in the server
    ofstream ServerDataFile(FileCSV);
    // Send to the Client what file the user need to give
    dio->write(UploadMessage);

    string row = "0";
    while (row != "//EOM_MARKER") {
        row = dio -> read();
        if (row == "//EOM_MARKER") {
            break;
        }
        ServerDataFile << row << endl;
    }


    dio -> write("Upload complete.\n");
    ServerDataFile.close();
}



void CommandUploadCSV::execute(SharedData* shared) {
    try{

        string TrainCSV = "ClassifiedFile.csv";
        string UploadTrain = "Please upload your local train CSV file.\n";

        string TestCSV = "UnclassifiedFile.csv";
        string UploadTest = "Please upload your local test CSV file.\n ";
        //dio -> write("Please upload your local train CSV file.\n");
        //string TrainSet = dio -> read(); // Content of the train cvs file
        //cout << TrainSet;
        //dio -> write("Upload Complete.\n");
  
        UploadFile(TrainCSV, UploadTrain);
        //dio -> write("Please upload your local test CSV file.\n");
        //string TestSet = dio -> read();// Content of the test cvs file
        //cout << TestSet;
        //dio -> write("Upload Complete.\n");
        UploadFile(TestCSV, UploadTest);
        /*InputCheck InCheck;
        string DataName = InCheck.FileName(PathClassifiedFile);
        DataImport data(PathClassifiedFile);
        data.ReadClassifiedData();
*/
    } catch (exception& invalid_null){
        return;
    };
    //DataImport data(path);
    //DataImport data(SharedInfo->GetPath());
    //data.ReadData();
}

string CommandUploadCSV::GetDescription() {
    return this->description;
}