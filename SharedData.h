// Eden Berman 318530474
// Liad Brettler 318517182

#ifndef HEADER_SHAREDDATA_H
#define HEADER_SHAREDDATA_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <thread>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fstream>
#include "DataImport.h"

using namespace std;

// class SharedData{
// private:
//     string path;
//     int* k;
//     string* metric;
//     DataImport* data;
// public:
//     SharedData();
//     ~SharedData();
//     void SetPath(string FilePath);


//     string GetPath();
//     int* GetK();
//     string* GetMetric();
//     DataImport* GetData(string* path);

// };

class SharedData {
private:
    string ClassifiedPath;
    string UnclassifiedPath;
    int k;
    string metric;
    DataImport* ClassifiedData;
    DataImport* UnclassifiedData;
    vector<string>* ResultsVector;
public:
    SharedData();

    ~SharedData();

    void SetClassifiedPath(string FilePath);
    string GetClassifiedPath();

    void SetUnclassifiedPath(string FilePath);
    string GetUnclassifiedPath();

    int GetK() const;
    void SetK(int& NewK);

    string GetMetric() const;
    void SetMetric(string& NewMetric);

    vector<string>* GetResultsVector() const;
    void SetResultsVector(string& label);

    DataImport* GetClassifiedData();
    DataImport* GetUnclassifiedData();


};

#endif //ADVANCEDPROGRAMMINGTASK4_SHAREDDATA_H
