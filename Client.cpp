// Eden Berman 318530474
// Liad Brettler 318517182
#include "Client.h"


// Command line: ./client.out <IP_Address> <Port_number>
int main(int argc, char* argv[]) {

    // Confirm that the three required arguments have been provided: the execute command, IP address, and port number.
    InputCheck InCheck;
    //InCheck.ValidNumberArgs(argc);

    // Verify that the IP address is in a valid IPv4 format and convert it to a char array if it is.
    string IPAddress = argv[1];
    InCheck.ValidIPv4Address(IPAddress);
    const char *BufferIPAddress = IPAddress.c_str();

    // Confirm that the port value is valid.
    int ClientPort = InCheck.ValidPortCheck(argv[2]);

    // Start the client and execute its functions.
    ClientClass client(BufferIPAddress, ClientPort);
    int SocketNumber = client.run();
    string Menu = "Server_Menu";
    //client.ClientInteraction(SocketNumber, Menu);
    SocketIO ServerSocketIO(SocketNumber);

    string OutputFile ="output";
    // Using functor to initialize the thread.
    // Functor taking object and the variables of this object and send it to the Thread constructor.
    thread SendThread([&client, &ServerSocketIO]()
                        { client.SendMessages(&ServerSocketIO); });
    //thread ReceiveThread(client.ReceiveMessages, SocketNumber, outputFile);
    thread ReceiveThread([&client, &ServerSocketIO, OutputFile]()
                        { client.ReceiveMessages(&ServerSocketIO, OutputFile); });
    SendThread.join();
    ReceiveThread.join();
    close(SocketNumber);
    cout<<"Client Closed"<<endl;


}