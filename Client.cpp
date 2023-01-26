// Eden Berman 318530474
// Liad Brettler 318517182

#include "Client.h"

// Command line: ./client.out <IP_Address> <Port_number>
int main(int argc, char* argv[]) {

    // Confirm that the three required arguments have been provided: the execute command, IP address, and port number.
    InputCheck InCheck;
    string FlagC = "c";
    InCheck.ValidNumberArgs(argc, FlagC);

    // Verify that the IP address is in a valid IPv4 format and convert it to a char array if it is.
    string IPAddress = argv[1];
    InCheck.ValidIPv4Address(IPAddress);
    const char *BufferIPAddress = IPAddress.c_str();

    // Confirm that the port value is valid.
    int ClientPort = InCheck.ValidPortCheck(argv[2]);

    // Start the client and execute its functions.
    ClientClass client(BufferIPAddress, ClientPort);
    int SocketNumber = client.run();
    SocketIO ServerSocketIO(SocketNumber);

    // Using functor to initialize the client's thread.
    thread ReceiveThread([&client, &ServerSocketIO]()
                        { client.ReceiveMessages(&ServerSocketIO); });
    ReceiveThread.join();
    close(SocketNumber);
}