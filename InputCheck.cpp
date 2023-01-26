// Eden Berman 318530474
// Liad Brettler 318517182

#include "InputCheck.h"

// Constructor & Destructor:
InputCheck::InputCheck() {};
InputCheck::~InputCheck() {};

// Check if the input string contains any characters other than digits and a single decimal point.
bool InputCheck::ValidDoubleVector(const string& input) const {
    bool FlagValidChars = true;
    bool FlagDecimalPointReached = false;
    const char* CharArrayValues = input.c_str();

    for (int i = 1; i < input.size(); i++) {
        if (!isdigit(CharArrayValues[i]) && CharArrayValues[i] != '.') {
            FlagValidChars = false;
            break;
        }
        if (CharArrayValues[i] == '.') {
            if (FlagDecimalPointReached) {
                FlagValidChars = false;
                break;
            }
            FlagDecimalPointReached = true;
        }
    }
    return FlagValidChars;
}

// Check if the correct number of arguments is passed.
void InputCheck::ValidNumberArgs(const int& argc, const string& flag) const {
    if (flag == "c" && argc != 3) {
        cerr << "Error: incorrect number of arguments." << endl;
        exit(1);
    } else if (flag == "s" && argc != 2) {
        cerr << "Error: incorrect number of arguments." << endl;
        exit(1);
    }
}

// Validate the server port number.
int InputCheck::ValidPortCheck(const string& PortString) const {

    try {
        // Validate that the port is a positive integer.
        int PortInt = ValidKNumber(PortString);

        // If the port isn't a positive integer, or is out of range, terminate the program.
        if (PortInt < 0 || PortInt > 65535) {
            cerr << "Error: invalid port number, must be in range [0-65535]" << endl;
            exit(1);
        }
        return PortInt;
    }
    catch (exception& invalid_port_number) {
        cerr << "Error: invalid port number, must be an integer." << endl;
        exit(1);
    }
}

// Validate the IP address.
void InputCheck::ValidIPv4Address(const string& ip) const {
    // Split the string into octets.
    vector<string> VecOctets;
    istringstream is(ip);
    string octet;

    // Splitting the IP address into octets by the '.' delimiter.
    while (getline(is, octet, '.')) {
        VecOctets.push_back(octet);
    }

    // Check that there are exactly 4 octets.
    if (VecOctets.size() != 4) {
        cerr << "Error: invalid IP address, must be exactly 4 octets." << endl;
        exit(1);
    }

    // Check that each octet is within the range 0-255.
    for (int i = 0; i < VecOctets.size(); ++i) {
        int OctetInt;
        try {
            OctetInt = std::stoi(VecOctets[i]);
            if (OctetInt < 0 || OctetInt > 255) {
                cerr << "Error: invalid IP address, each octet must be within the range 0-255." << endl;
                exit(1);
            }
        }
        catch(exception& invalid_IP_number) {
            cerr << "Error: invalid IP address, each octet must be an integer." << endl;
            exit(1);
        }
    }
}

// Convert a vector of strings into a vector of doubles.
// When we call this method the vector is for sure pure doubls
vector<double> InputCheck::StringToDouble(const vector<string>& s) const {

    vector<double> vec;
    if (s.empty()) {
        cerr << "Error: File contain Empty Vector." << endl;
    }
    for (unsigned int i = 0; i < s.size(); i++) {
        try {
            double feature = std::strtod(s.at(i));
            vec.push_back(feature);
        }
        catch (const invalid_argument& e) {
            cerr << "Error: File contain invalid data." << endl;
        }
    }
    return vec;
}

// Convert a vector of strings into a vector of doubles.
bool InputCheck::ValidStringToDouble(const vector<string>& s) const{
    vector<double> vec;
    if (s.empty()) {
        return false;
    }

    for (unsigned int i = 0; i < s.size(); i++) {
        try {
            double feature = std::strtod(s.at(i));
            vec.push_back(feature);
        }
        catch (const invalid_argument& e) {
            return false;
        }
    }
    return true;
}

// Check if two vectors are of the same size.
bool InputCheck::ValidVectorSizeCheck(const vector<double>& a, const vector<double>& b) const {
    if (a.size() != b.size()) {
        return false;
    }
    return true;
}

// Convert string to int.
int InputCheck::ValidKNumber(const string& k) const {
    try {
        const char* CharArrayK = k.c_str();
        for (int i = 0; i < k.size(); i++) {
            if (!isdigit(CharArrayK[i])) {
                return -1;
            }
        }
        int num = std::stoi(k);
        if (num > 0) {
            return num;
        }
        else {
            return -1;
        }
    }
    catch (exception& invalid_argument) {
        return -1;
    }
}

// Check if the file exists and is not damaged.
bool InputCheck::ValidFilePath(string DataName) {
    try {
        ifstream file(DataName.c_str());
        if (!file.good() || !file.is_open()) {
            return false;
        }
    }
    catch (exception& damaged_file) {
        return false;
    }
    return true;
}

// Check if the file contains any white space characters.
// StringVector is the row without the last element
bool InputCheck::WhitespacesFileCheck(const vector<string>& StringVector) const {

    if (StringVector.empty()) {
        cerr << "Error: File contain Empty Vector." << endl;
        return false;
    }
    for (int i = 0; i < StringVector.size(); i++) {
        const char *CharArray = StringVector[i].c_str();
        for (int i = 0; i < StringVector[i].size(); i++) {
            if (CharArray[i] == ' ') {
                cerr << "Error: CSV file can't contain whitespaces." << endl;
                return false;
            }
        }
        if (StringVector[i].empty()) {
            cerr << "Error: CSV file can't contain empty rows." << endl;
            return false;
        }
    }
    return true;
}

// Check if the label is not empty or only with whitespaces.
bool InputCheck::ValidLabel(const string& label) const {

    if (label.empty()) {
        return false;
    }

    // find_first_not_of function searching in a string if there is any char that is not [" \t\n\v\f\r"],
    // If the function finds she will return the position of this char. Else she will return npos.
    // Meaning if npos returns our string is contains only whitespaces.
    if (label.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        return false;
    }
    return true;
}

// Check if the file is empty.
bool InputCheck::EmptyFileCheck(const map<vector<double>, string> &DataMap) const {
    if (DataMap.empty()) {
        return false;
    }
    return true;
}

// Check if a valid metric type was received.
bool InputCheck::ValidDistanceMetric(const string &metric) const {
    if (metric == "AUC" || metric == "MAN" || metric == "CHB" || metric == "CAN" || metric == "MIN") {
        return true;
    } else {
        return false;
    }
}
