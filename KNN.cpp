// Eden Berman 318530474
// Liad Brettler 318517182

#include "KNN.h"

// Constructor & Destructor:
KNN::KNN(const int& KNum, const map<vector<double>, string>& FullData, const string& MetricType,
         const vector<double>& v) : k(KNum), DataMap(FullData), metric(MetricType), vec(v) {}
KNN::~KNN() {};

// Detect the most common label from the 'KNearestNeighbors' function. This will classify the sample we wish to predict.
string KNN::predict() const {
    vector<string> KLabels = KNearestNeighbors();
    map<string, int> counts;
    for (const auto& label : KLabels) {
        counts[label]++;
    }

    string MostCommon;
    int MaxCount = 0;
    for (const auto& label : counts) {
        if (label.second > MaxCount) {
            MostCommon = label.first;
            MaxCount = label.second;
        }
    }
    return MostCommon;
};

// Create a vector of strings containing the labels of the K nearest neighbors derived from the sorted map.
vector<string> KNN::KNearestNeighbors() const {
    multimap<double, string> DistanceLabelMap = train();
    vector<string> KLabels;
    int count = 1;

    for (auto& kv : DistanceLabelMap) {
        KLabels.push_back(kv.second);
        if (count == k) {
            break;
        }
        count++;
    }
    return KLabels;
};

// Calculate the distance between all data vectors to the received vector according to the appropriate distance metric.
// Insert all distance-label pairs into a multimap which will sort them by key.
multimap<double, string> KNN::train() const {
    DistanceCalc dc;
    multimap<double, string> DistanceLabelMap;
    for (const auto& kv : DataMap) {
        const auto& key = kv.first; // key = vector
        const auto& value = kv.second; // value = label

        if (metric == "AUC") {
            DistanceLabelMap.insert(make_pair(dc.euclidean(key, vec), value));
        }
        if (metric == "MAN") {
            DistanceLabelMap.insert(make_pair(dc.manhattan(key, vec), value));
        }
        if (metric == "CHB") {
            DistanceLabelMap.insert(make_pair(dc.chebyshev(key, vec), value));
        }
        if (metric == "CAN") {
            try {
                DistanceLabelMap.insert(make_pair(dc.canberra(key, vec), value));
            }
            catch (int& ex) {
                cerr << "Error: division by zero." << endl;
            }
        }
        if (metric == "MIN") {
            DistanceLabelMap.insert(make_pair(dc.minkowski(key, vec), value));
        }
    }
    return DistanceLabelMap;
};