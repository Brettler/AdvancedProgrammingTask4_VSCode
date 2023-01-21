// Eden Berman 318530474
// Liad Brettler 318517182

#include "SharedData.h"

SharedData::SharedData() {}
SharedData::~SharedData() {}

string* SharedData::GetPath() {
    return this -> path;
}

int* SharedData::GetK() {
   return this -> k;
}

string* SharedData::GetMetric() {
    return this -> metric;
}