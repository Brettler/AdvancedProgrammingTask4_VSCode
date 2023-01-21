// Eden Berman 318530474
// Liad Brettler 318517182



#include "Command.h"




/*UploadCSV::UploadCSV(DefaultIO* dio, SharedData* SharedInfo)
:Command(dio,"1. upload an unclassified csv data file", SharedInfo){};*/

CommandUploadCSV::CommandUploadCSV(DefaultIO* dio, SharedData* SharedInfo)
        :Command(dio, SharedInfo){
    this -> description = "1. upload an unclassified csv data file";
};
CommandUploadCSV::~CommandUploadCSV(){};

/*void CommandUploadCSV::UploadFile(string FileCSV, string UploadMessage){
    // Creating new file to send to the server
    ofstream ServerDataFile(FileCSV);
    // Send to the Client what file the user need to give
    dio->write(UploadMessage);



    string row = "0";
    while (row != "done") {
        row = dio->read();
        ServerDataFile << row << endl;
    }


    dio->write("Upload complete." + row);
    ServerDataFile.close();

}*/



void CommandUploadCSV::execute(SharedData* SharedInfo) {
    try{

        string trainFile = "trainFile.csv";
        string testFile = "testFile.csv";

        dio -> write("Please upload your local train CSV file.\n");
        string TrainSet = dio -> read(); // Content of the train cvs file
        dio -> write("Upload Complete.\n");

        dio -> write("Please upload your local test CSV file.\n");
        string TestSet = dio -> read();// Content of the test cvs file
        dio -> write("Upload Complete.\n");

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