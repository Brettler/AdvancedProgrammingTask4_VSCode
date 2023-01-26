// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor
CommandClassify::CommandClassify(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "3. classify data\n";
        }

CommandClassify::~CommandClassify(){}

void CommandClassify::execute(SharedData* shared) {
    string label;
    if (shared -> ClassifiedData == nullptr) {
        dio -> write("please upload data\n");
        return;
    }

    for (int i = 0; i < shared -> GetUnclassifiedData() -> UnclassifiedVectors.size(); i++) {
        // Create KNN object;
        KNN classifier(shared -> GetK(), shared -> GetClassifiedData() -> DataMap, shared -> GetMetric(),
        shared -> GetUnclassifiedData() -> UnclassifiedVectors[i]);
        label = classifier.predict();
        // We save each label in a vector;
        shared -> SetResultsVector(label);
    }
    dio -> write("classifying data complete\n");
}

string CommandClassify::GetDescription() {
    return this -> description;
}