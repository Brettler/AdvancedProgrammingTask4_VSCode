// Eden Berman 318530474
// Liad Brettler 318517182

#include "Command.h"

// Constructor & Destructor:
Command::Command(DefaultIO* dio, SharedData* shared):dio(dio), shared(shared) {}
Command::~Command(){}

// Methods:
void Command::execute(SharedData* shared) {}
string Command::GetDescription() {}