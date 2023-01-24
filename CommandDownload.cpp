// Eden Berman 318530474
// Liad Brettler 318517182


#include "Command.h"


CommandDownload::CommandDownload(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "5. download results\n";
        }

CommandDownload::~CommandDownload(){}

/*string Command::GetDescription() {
    return this->description;
}*/
/*SharedData* Command::GetSharedData() {
    return this->shared;
}*/

void CommandDownload::execute(SharedData* shared) {
    string index;
    
    try {
        if(shared->GetClassifiedData()->GetDataMap().size() == 0) {
            dio -> write("please upload data\n");
            return;
        }
    } catch (int& nullptr_ex) {
        dio -> write("please upload data\n");
        return;
    }

    try {
        if((*shared -> GetResultsVector()).size() == 0) {
            dio -> write("please classify the data\n");
            return;
        }
    } catch (int& nullptr_ex) {
        dio -> write("please classify the data\n");
        return;
    }
    dio -> write("good\n");


    if (dio -> read() == "err_exp") {
        return;
    }
    cout << "loop: " <<endl;
    for (int i=0; i < (*shared -> GetResultsVector()).size(); i++) {
        index = to_string(i +1);
        dio -> write(index +" "+(*shared -> GetResultsVector()).at(i) + "\n");
    }
    dio -> write("Done.\n");
}

string CommandDownload::GetDescription() {
    return this -> description;
}