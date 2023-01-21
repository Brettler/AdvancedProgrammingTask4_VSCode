// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

CommandExit::CommandExit(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared){
    this -> description = "8.exit\n";
}
CommandExit::~CommandExit(){}

void CommandExit::execute(SharedData* shared) {}

string CommandExit::GetDescription() {
    return this->description;
}