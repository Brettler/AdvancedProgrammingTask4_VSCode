// Eden Berman 318530474
// Liad Brettler 318517182

#pragma once
#ifndef HEADER_DataImport
#define HEADER_DataImport

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <map>
#include "InputCheck.h"
using namespace std;

class DataImport {
public:
    string DataName;
    ifstream file;
    map<vector<double>, string> DataMap;
    vector<vector<double>> UnclassifiedVectors;
    // Constructor & Destructor:
    explicit DataImport(const string& DataName);
    ~DataImport();
    // Functions:
    bool ReadClassifiedData();
    bool ReadUnclassifiedData(map<vector<double>, string> TrainMap);
    // Getters:
    const map<vector<double>, string>& GetDataMap() const;
};
#endif
