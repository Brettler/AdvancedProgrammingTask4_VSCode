// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
CommandExit::CommandExit(DefaultIO* dio, SharedData* shared)
        :Command(dio, shared) {
    this -> description = "8. exit\n";
}
CommandExit::~CommandExit() {}

// Returns to its CLI instance to close this client.
void CommandExit::execute(SharedData* shared) {
    return;
}

// Command description.
string CommandExit::GetDescription() {
    return this -> description;
}