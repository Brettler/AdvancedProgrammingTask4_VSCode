// Eden Berman 318530474
// Liad Brettler 318517182


#include "Command.h"



CommandSettingsKNN::CommandSettingsKNN(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
            this -> description = "2. algorithm settings\n";
        }

CommandSettingsKNN::~CommandSettingsKNN(){}

/*string Command::GetDescription() {
    return this->description;
}*/
/*SharedData* Command::GetSharedData() {
    return this->shared;
}*/

void Command::execute(SharedData* shared) {



}