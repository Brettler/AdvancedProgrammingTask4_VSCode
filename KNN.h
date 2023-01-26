// Eden Berman 318530474
// Liad Brettler 318517182

#pragma once
#ifndef HEADER_KNN
#define HEADER_KNN

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include <tuple>
#include "DistanceCalc.h"
#include "DataImport.h"
using namespace std;

class KNN {
private:
    const int& k;
    const string& metric;
    const vector<double>& vec;
    const map<vector<double>, string>& DataMap;
public:
    // Constructor & Destructor:
    KNN(const int& KNum, const map<vector<double>, string>& FullData, const string& MetricType,
        const vector<double>& v);
    ~KNN();
    // Functions:
    multimap<double, string> train() const;
    vector<string> KNearestNeighbors() const;
    string predict() const;
};
#endif
