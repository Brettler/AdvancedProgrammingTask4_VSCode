// Eden Berman 318530474
// Liad Brettler 318517182


#include "Command.h"


Command::Command(DefaultIO* dio, SharedData* shared):dio(dio), shared(shared) {}

Command::~Command(){}

/*string Command::GetDescription() {
    return this->description;
}*/
/*SharedData* Command::GetSharedData() {
    return this->shared;
}*/

void Command::execute(SharedData* shared) {}