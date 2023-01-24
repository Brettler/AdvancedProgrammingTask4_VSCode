// Eden Berman 318530474
// Liad Brettler 318517182


#include "Command.h"


CommandClassify::CommandClassify(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "3. classify data\n";
        }

CommandClassify::~CommandClassify(){}

/*string Command::GetDescription() {
    return this->description;
}*/
/*SharedData* Command::GetSharedData() {
    return this->shared;
}*/

void CommandClassify::execute(SharedData* shared) {
    string label;
    try {
        cout << "We are in try" << endl;
        if(shared->GetClassifiedData()->GetDataMap().size() == 0) {
            cout << "We are in try in if" << endl;
            dio -> write("please upload data\n");
            return;
        }
    } catch (int& nullptr_ex) {
        cout << "We are in catch" << endl;
        dio -> write("please upload data\n");
        return;
    }
    cout << "before for loop" << endl;  
    for (int i = 0; i < shared -> GetUnclassifiedData() -> UnclassifiedVectors.size(); i++) {
        // Create KNN object;
        cout << "making classifier" << endl;
        KNN classifier(shared -> GetK(), shared -> GetClassifiedData() -> DataMap, shared -> GetMetric(),
        shared -> GetUnclassifiedData() -> UnclassifiedVectors[i]);
        cout << "calling predict function" << endl;
        label = classifier.predict();
        cout << "set results vector" << endl;
        // We save each label in a vector;
        shared -> SetResultsVector(label);
    }
    cout << "writing back to the client" << endl;
    dio -> write("classifying data complete\n");
}

string CommandClassify::GetDescription() {
    return this -> description;
}