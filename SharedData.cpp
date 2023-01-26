// Eden Berman 318530474
// Liad Brettler 318517182

#include "SharedData.h"

SharedData::SharedData(int ClientSockNum) {
    this -> CLISockNum = ClientSockNum;
    k = 5;
    metric = "AUC";
    ResultsVector = new vector<string>;
    ClassifiedData = nullptr;
    UnclassifiedData = nullptr;
}

SharedData::~SharedData() {
    // if (k != nullptr) {
    //      delete k;
    // }
    // if (metric != nullptr) {
    //      delete metric;
    // }
    if (ClassifiedData != nullptr) {
        delete ClassifiedData;
    }
    if (UnclassifiedData != nullptr) {
        delete UnclassifiedData;
    }
    delete ResultsVector;

}

void SharedData::SetClassifiedPath(string FileClassifiePath) {
    this -> ClassifiedPath = FileClassifiePath; 
}

string SharedData::GetClassifiedPath() {
    return this -> ClassifiedPath;
}

void SharedData::SetUnclassifiedPath(string FileUnclassifiedPath) {
    this -> UnclassifiedPath = FileUnclassifiedPath; 
}

string SharedData::GetUnclassifiedPath() {
    return this -> UnclassifiedPath;
}

int SharedData::GetK() const{ 
   return this -> k;
}

void SharedData::SetK(int NewK) {
    this -> k = NewK;
}

string SharedData::GetMetric() const{
    return this -> metric;
}

void SharedData::SetMetric(string NewMetric) {
    this -> metric = NewMetric;
}

vector<string>* SharedData::GetResultsVector() const {
    return this -> ResultsVector;
}

void SharedData::SetResultsVector(string& label){
    this -> ResultsVector -> push_back(label);
}

DataImport* SharedData::GetClassifiedData() {
    return this -> ClassifiedData;
}

void SharedData::SetClassifiedData() {
    if (ClassifiedData == nullptr) {
        ClassifiedData = new DataImport(ClassifiedPath); 
    } else {
        delete ClassifiedData;
        ClassifiedData = new DataImport(ClassifiedPath);
    }
}

DataImport* SharedData::GetUnclassifiedData() {
    return this -> UnclassifiedData;
}

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