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
    bool ValidClientMessage(const string& StringInput) const;
    bool ValidVectorSizeCheck(const vector<double>& a, const vector<double>& b) const;
    bool ValidDoubleVector(const string& input) const;
    void ValidLabel(const string& label) const;
    int ValidKNumber(const string& k) const;
    int ValidPortCheck(const string& PortString) const;
    string FileName(string DataName) const;
    void ValidNumberArgs(const int& argc) const;
    void ValidIPv4Address(const string& ip) const;
    void WhitespacesFileCheck(const vector<string>& feature) const;
    void EmptyFileCheck(const map<vector<double>, string>& DataMap) const;
};
#endif