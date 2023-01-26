// Eden Berman 318530474
// Liad Brettler 318517182

#pragma once
#ifndef HEADER_InputCheck
#define HEADER_InputCheck

#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>
using namespace std;

class InputCheck {
public:
    // Constructor & Destructor:
    InputCheck();
    ~InputCheck();
    // Functions:
    vector<double> StringToDouble(const vector<string>& s) const;
    bool ValidDistanceMetric(const string& metric) const;
    bool ValidVectorSizeCheck(const vector<double>& a, const vector<double>& b) const;
    bool ValidDoubleVector(const string& input) const;
    bool ValidLabel(const string& label) const;
    int ValidKNumber(const string& k) const;
    int ValidPortCheck(const string& PortString) const;
    bool ValidFilePath(string DataName);
    void ValidNumberArgs(const int& argc, const string& flag) const;
    void ValidIPv4Address(const string& ip) const;
    bool WhitespacesFileCheck(const vector<string>& feature) const;
    bool EmptyFileCheck(const map<vector<double>, string>& DataMap) const;
    bool ValidStringToDouble(const vector<string>& s) const;
};
#endif