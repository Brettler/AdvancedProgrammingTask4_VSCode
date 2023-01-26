// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandClassify::CommandClassify(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "3. classify data\n";
        }
CommandClassify::~CommandClassify() {}

// Uploading the classified and unclassified CSV files.
void CommandClassify::execute(SharedData* shared) {
    string label;

    // If the data has yet to be uploaded, return.
    if (shared -> ClassifiedData == nullptr) {
        dio -> write("please upload data\n");
        return;
    }

    // Create a KNN object to classify each sample, and add the label to the shared results vector.
    for (int i = 0; i < shared -> GetUnclassifiedData() -> UnclassifiedVectors.size(); i++) {
        KNN classifier(shared -> GetK(), shared -> GetClassifiedData() -> DataMap, shared -> GetMetric(),
        shared -> GetUnclassifiedData() -> UnclassifiedVectors[i]);
        label = classifier.predict();
        shared -> SetResultsVector(label);
    }
    dio -> write("classifying data complete\n");
}

// Command description.
string CommandClassify::GetDescription() {
    return this -> description;
}