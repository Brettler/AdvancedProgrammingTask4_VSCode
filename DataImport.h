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
private:
    string DataName;
    string UnclassifiedDataName;
    ifstream file;
    map<vector<double>, string> DataMap;

public:
    // Constructor & Destructor:
    explicit DataImport(const string& DataName);
    ~DataImport();
    // Functions:
    void ReadClassifiedData();
    // Getters:
    const map<vector<double>, string>& GetDataMap() const;
};
#endif
