// Eden Berman 318530474
// Liad Brettler 318517182

#include "SharedData.h"

// Constructor & Destructor:
SharedData::SharedData(int ClientSockNum) {
    this -> CLISockNum = ClientSockNum;
    k = 5;
    metric = "AUC";
    ResultsVector = new vector<string>;
    ClassifiedData = nullptr;
    UnclassifiedData = nullptr;
}
SharedData::~SharedData() {
    if (ClassifiedData != nullptr) {
        delete ClassifiedData;
    }
    if (UnclassifiedData != nullptr) {
        delete UnclassifiedData;
    }
    delete ResultsVector;
}

// Get classified file path.
string SharedData::GetClassifiedPath() {
    return this -> ClassifiedPath;
}

// Set classified file path.
void SharedData::SetClassifiedPath(string FileClassifiePath) {
    this -> ClassifiedPath = FileClassifiePath; 
}

// Get unclassified file path.
string SharedData::GetUnclassifiedPath() {
    return this -> UnclassifiedPath;
}

// Set unclassified file path.
void SharedData::SetUnclassifiedPath(string FileUnclassifiedPath) {
    this -> UnclassifiedPath = FileUnclassifiedPath; 
}

// Get K value.
int SharedData::GetK() const { 
   return this -> k;
}

// Set K value.
void SharedData::SetK(int NewK) {
    this -> k = NewK;
}

// Get metric value.
string SharedData::GetMetric() const {
    return this -> metric;
}

// Set metric value.
void SharedData::SetMetric(string NewMetric) {
    this -> metric = NewMetric;
}

// Get vector containing the classification results.
vector<string>* SharedData::GetResultsVector() const {
    return this -> ResultsVector;
}

// Set vector containing the classification results.
void SharedData::SetResultsVector(string& label) {
    this -> ResultsVector -> push_back(label);
}

// Get the classified data.
DataImport* SharedData::GetClassifiedData() {
    return this -> ClassifiedData;
}

// Set the classified data using a DataImport object.
void SharedData::SetClassifiedData() {
    if (ClassifiedData == nullptr) {
        ClassifiedData = new DataImport(ClassifiedPath); 
    } else {
        delete ClassifiedData;
        ClassifiedData = new DataImport(ClassifiedPath);
    }
}

// Get the unclassified data.
DataImport* SharedData::GetUnclassifiedData() {
    return this -> UnclassifiedData;
}

// Set the unclassified data using a DataImport object.
void SharedData::SetUnclassifiedData() {
    if (UnclassifiedData == nullptr) {
        UnclassifiedData = new DataImport(UnclassifiedPath); 
    } else {
        delete UnclassifiedData;
        delete ResultsVector;
        UnclassifiedData = new DataImport(UnclassifiedPath);
        ResultsVector = new vector<string>;
    }
}