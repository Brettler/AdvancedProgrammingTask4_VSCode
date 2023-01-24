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
bool DataImport::ReadClassifiedData() {

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
        if (!ic.ValidLabel(label)){
            return false;
        }

        sample.pop_back();
        // Check if the row contains any white space characters.
        if (!ic.WhitespacesFileCheck(sample)){
            return false;
        }

        vector<double> SampleDouble;

        if (!ic.ValidStringToDouble(sample)){
            return false;
        } else {
            // Convert the strings into doubles.
            SampleDouble = ic.StringToDouble(sample);
        }

        // Compare the size of the first vector against all other vectors to make sure they're the same.
        // If they are all the same size, continue. Otherwise, terminate the program.
        if (FlagFirstIter) {
            buffer = SampleDouble;
            FlagFirstIter = false;
        }
        else {
            bool ValidVectorSize = ic.ValidVectorSizeCheck(buffer, SampleDouble);
            if (!ValidVectorSize) {
                return false;
            }
        }

        // If we come across a vector that already exists in the map, skip.
        // Otherwise, insert into map.
        if (this -> DataMap.find(SampleDouble) != this -> DataMap.end()) {
            continue;
        }
        else {
            this -> DataMap[SampleDouble] = label;
        }
    }

    // Check if the file is empty by checking if the map is empty.
    if (!ic.EmptyFileCheck(this -> DataMap)){
        return false;
    }

    return true;
}

bool DataImport::ReadUnclassifiedData(map<vector<double>, string> TrainMap){
    ifstream data(this->DataName);
    string row;
    InputCheck ic;
    // Acess to the data map first vector. 
    // This use is just after we processed the train file from the user.
    vector<double> FirstVector = TrainMap.begin()->first;

    // Each line in the csv file will be inserted into 'row' as a string.
    while (getline(data, row))
    {
        vector<string> sample;
        stringstream ss(row);
        string feature;

        // Parse the row to extract the sample features and label.
        while (getline(ss, feature, ',')) {
            sample.push_back(feature);
        }

        // Check if the row contains any white space characters.
        if (!ic.WhitespacesFileCheck(sample)){
            //cout << " return false because WhitespacesFileCheck\n";
            return false;
        }

        vector<double> SampleDouble;

        if (!ic.ValidStringToDouble(sample)){
            //cout << " return false because ValidStringToDouble\n";
            return false;
        } else {
            // Convert the strings into doubles.
            SampleDouble = ic.StringToDouble(sample);
        }

        for (int i = 0 ; i< FirstVector.size(); i++) {
            cout << FirstVector.at(i) << " ";
        }
        cout << endl;
        //cout << "TrainSetVector size is: " << FirstVector.size() << endl;

        // Compare the size of the first vector of the training set against all other vectors to make sure they're the same.
        // If they are all the same size, continue. Otherwise, terminate the program.
        bool ValidVectorSize = ic.ValidVectorSizeCheck(FirstVector, SampleDouble);
        if (!ValidVectorSize) {
            //cout << " return false because ValidVectorSizeCheck\n";
            return false;
        }

        this -> UnclassifiedVectors.push_back(SampleDouble);
    }
    return true;
}


// Getters:
const map<vector<double>, string>& DataImport::GetDataMap() const {
    return this -> DataMap;
}

