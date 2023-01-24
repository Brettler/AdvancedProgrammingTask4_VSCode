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
}

string CommandClassify::GetDescription() {
    return this -> description;
}