// Eden Berman 318530474
// Liad Brettler 318517182
#include "Server.h"

// Command line: ./server.out <port_number>
int main(int argc, char* argv[]) {

    // Confirm that the three required arguments have been provided: the execute command, file path, and port number.
    InputCheck InCheck;
    string FlagS = "s";
    InCheck.ValidNumberArgs(argc, FlagS);
    const int ServerPort = InCheck.ValidPortCheck(argv[1]);

    // Start the server and execute its functions.
    ServerClass server(ServerPort);
    server.run();
    for (auto &thread : server.ThreadPool) {
        thread.join();
    }
}
