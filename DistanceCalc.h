// Eden Berman 318530474
// Liad Brettler 318517182

#pragma once
#ifndef HEADER_DistanceCalc
#define HEADER_DistanceCalc
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <map>
using namespace std;

class DistanceCalc {
public:
    // Constructor & Destructor:
    DistanceCalc();
    ~DistanceCalc();
    // Functions:
    double euclidean(const vector<double>& v1, const vector<double>& v2) const;
    double manhattan(const vector<double>& v1, const vector<double>& v2) const;
    double chebyshev(const vector<double>& v1, const vector<double>& v2) const;
    double canberra(const vector<double>& v1, const vector<double>& v2) const;
    double minkowski(const vector<double>& v1, const vector<double>& v2, double p = 2) const;
};
#endif