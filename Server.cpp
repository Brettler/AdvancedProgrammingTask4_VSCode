// Eden Berman 318530474
// Liad Brettler 318517182
#include "Server.h"

// Command line: ./server.out <port_number>
int main(int argc, char* argv[]) {

    // Confirm that the three required arguments have been provided: the execute command, file path, and port number.
    InputCheck InCheck;
    //InCheck.ValidNumberArgs(argc);
    const int ServerPort = InCheck.ValidPortCheck(argv[1]);

    // Start the server and execute its functions.
    ServerClass server(ServerPort);
    server.run();

    /*

    // Validate each element based on its type.
    string DataName = InCheck.FileName(argv[1]);


    // Create a map from the data file in which the key is a vector and the value is a label.
    DataImport DataFile(DataName);
    DataFile.ReadData();

    // Start the server and execute its functions.
    ServerClass server(DataFile.GetDataMap(), ServerPort);
    server.run();

     */
}
