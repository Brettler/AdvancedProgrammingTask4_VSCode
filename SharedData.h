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
using namespace std;

class SharedData{
private:
    string* path;
    int* k;
    string* metric;
public:
    SharedData();
    ~SharedData();
    string* GetPath();
    int* GetK();
    string* GetMetric();

/*    string path;
    int k;
    string metric;
    //vector<fixdReport> fixdRports;
    const map<vector<double>, string>& DataMap;
    ShareStruct() {
        string path;
        int k;
        string metric;
    }*/

};




#endif //ADVANCEDPROGRAMMINGTASK4_SHAREDDATA_H
