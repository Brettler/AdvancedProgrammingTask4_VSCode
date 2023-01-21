// Eden Berman 318530474
// Liad Brettler 318517182
#include "DataImport.h"

// Constructor & Destructor

DataImport::DataImport(const string& DataName) {
    this -> DataName = DataName;
    file.open(DataName);
};

DataImport::~DataImport() {
    file.close();
}

// Converts data from a CSV file into a map of vector-label pairs.
void DataImport::ReadClassifiedData() {

    ifstream data(this->DataName);
    vector<double> buffer;
    string row;
    bool FlagFirstIter = true;
    InputCheck ic;

    // Each line in the csv file will be inserted into 'row' as a string.
    while (getline(data, row))
    {
        vector<string> sample;
        stringstream ss(row);
        string label;
        string feature;

        // Parse the row to extract the sample features and label.
        while (getline(ss, feature, ',')) {
            sample.push_back(feature);
        }

        label = sample.back();
        // Checking if the label is empty or just with whitespaces.
        ic.ValidLabel(label);

        sample.pop_back();
        // Check if the row contains any white space characters.
        ic.WhitespacesFileCheck(sample);

        // Convert the strings into doubles.
        vector<double> SampleDouble = ic.StringToDouble(sample);

        // Compare the size of the first vector against all other vectors to make sure they're the same.
        // If they are all the same size, continue. Otherwise, terminate the program.
        if (FlagFirstIter) {
            buffer = SampleDouble;
            FlagFirstIter = false;
        }
        else {
            bool ValidVectorSize = ic.ValidVectorSizeCheck(buffer, SampleDouble);
            if (!ValidVectorSize) {
                cerr << "Error: Vectors in the file must be in the same size." << endl;
                exit(1);
            }
        }

        // If we come across a vector that already exists in the map, skip.
        // Otherwise, insert into map.
        if (DataMap.find(SampleDouble) != DataMap.end()) {
            continue;
        }
        else {
            DataMap[SampleDouble] = label;
        }
    }

    // Check if the file is empty by checking if the map is empty.
    ic.EmptyFileCheck(DataMap);
}

// Getters:
const map<vector<double>, string>& DataImport::GetDataMap() const {
    return DataMap;
}

