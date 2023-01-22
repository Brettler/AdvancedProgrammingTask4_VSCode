// Eden Berman 318530474
// Liad Brettler 318517182

#include "SharedData.h"

SharedData::SharedData() {
    k = nullptr;
    metric = nullptr;
    ClassifiedData = nullptr;
    UnclassifiedData = nullptr;
}

SharedData::~SharedData() {
    if (k != nullptr) {
         delete k;
    }
    if (metric != nullptr) {
         delete metric;
    }
    if (ClassifiedData != nullptr) {
        delete ClassifiedData;
    }
    if (UnclassifiedData != nullptr) {
        delete UnclassifiedData;
    }
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


int* SharedData::GetK() {
   return this -> k;
}

string* SharedData::GetMetric() {
    return this -> metric;
}

DataImport* SharedData::GetClassifiedData() {
    if (ClassifiedData == nullptr) {
        ClassifiedData = new DataImport(ClassifiedPath); 
    }
    return this -> ClassifiedData;
}

DataImport* SharedData::GetUnclassifiedData() {
    if (UnclassifiedData == nullptr) {
        UnclassifiedData = new DataImport(UnclassifiedPath); 
    }
    return this -> UnclassifiedData;
}