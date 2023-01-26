// Eden Berman 318530474
// Liad Brettler 318517182

#include "DistanceCalc.h"

// Constructor & Destructor:
DistanceCalc::DistanceCalc() {};
DistanceCalc::~DistanceCalc() {};

// Euclidean: Sqrt(Sum(pi - qi)^2)	Minkowski p = 2.
double DistanceCalc::euclidean(const vector<double>& v1, const vector<double>& v2) const {
    return minkowski(v1, v2, 2);
}

// Manhattan: Sum(|pi - qi|)    Minkowski p = 1.
double DistanceCalc::manhattan(const vector<double>& v1, const vector<double>& v2) const {
    return minkowski(v1, v2, 1);
}

// Chebyshev: Max(|pi - qi|)
double DistanceCalc::chebyshev(const vector<double>& v1, const vector<double>& v2) const {

    double dis = 0;
    double max = 0;
    for (int i = 0; i < v1.size(); i++) {
        dis = abs(v1.at(i) - v2.at(i));
        if (dis > max) {
            max = dis;
        }
    }
    return (dis);
}

// Canberra: Sum((|pi - qi|)/(|pi|+|qi|))
double DistanceCalc::canberra(const vector<double>& v1, const vector<double>& v2) const {

    double dis = 0;
    double top, bottom;
    for (int i = 0; i < v1.size(); i++) {
        top = abs(v1.at(i) - v2.at(i));
        bottom = abs(v1.at(i)) + abs(v2.at(i));
        if (bottom == 0) {
            throw 0;
        }
        dis += top / bottom;
    }
    return (dis);
}

// Minkowski: (Sum((|pi - qi|)^P))^(1/P)    Minkowski p = 2.
double DistanceCalc::minkowski(const vector<double>& v1, const vector<double>& v2, const double p) const {

    double dis = 0;
    for (int i = 0; i < v1.size(); i++) {
        dis += pow(abs(v1.at(i) - v2.at(i)), p);
    }
    return pow(dis, (1 / p));
}
