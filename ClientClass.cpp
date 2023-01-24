// Eden Berman 318530474
// Liad Brettler 318517182
#include "ClientClass.h"

// Constructor
ClientClass::ClientClass(const char* BufferIPAddress, int ClientPort) {
    this -> BufferIPAddress = BufferIPAddress;
    this -> ClientPort = ClientPort;
}

// Create a connection with the server and send it the user input.
int ClientClass::run() {

    // Initialize the socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
    }

    // Specify the IP address and port number.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(BufferIPAddress);
    sin.sin_port = htons(ClientPort);

    // Attempt to connect to the server. If the connection fails, display an error message and exit the program.
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
        exit(1);
    }
    return sock;
}


bool ClientClass::InterfaceSendFile (string& path) {

    ifstream FileCSV(path);
    string TrainContent((istreambuf_iterator<char>(FileCSV)), istreambuf_iterator<char>());
    FileCSV.close();

    // We will add 'end-of-message' marker to know when we finished reading the messege
    Socket->write(TrainContent + "\n" + "//EOM_MARKER\n");
    string response = Socket->read(); // the client will read: upload complete / invalid input
    cout << response << endl;
    if (response == "invalid input") {
        return false;
    }
    response = Socket->read(); // the client will read: "Please enter the path to the test file:
    cout << response << endl;
    string TestPath;
    cin >> TestPath;
    //cout << "Input user for test path is: " << TestPath << endl;
    bool ValidFilePath = InCheck.ValidFilePath(TestPath);
    //cout << "bool ValidFilePath = " << ValidFilePath << endl;
    if (!ValidFilePath){
        //cout << "returning false in: if (!InCheck.ValidFilePath(TestPath) \n ";
        return false;
    }
    // Read the contents of the file
    ifstream TestCSV(TestPath);
    string TestContent((istreambuf_iterator<char>(TestCSV)), istreambuf_iterator<char>());
    TestCSV.close();
    // Send the contents of the file to the server
    Socket->write(TestContent + "\n" + "//EOM_MARKER\n");
    response = Socket->read(); // the client will read: upload complete / invalid input
    if (response == "invalid input") {
        return false;
    } else {
        cout << response << endl; // Upload Complete
    }
    return true;
}




// void ClientClass::SendMessages(DefaultIO* ServerSocket) {
//     this -> Socket = ServerSocket;
//     ifstream in("input.txt");
//     string input;
//     string path;
//     while(input!="8"){
//         getline(in,input);
//         ServerSocket -> write(input);
//         if(input=="1"){
//             cin >> path;
//             InterfaceSendFile (path);
//             /*getline(in,input);
//             while(input!="done"){
//                 getline(in,input);
//                 ServerSocket -> write(input)*/;
//         }
//     }
// }
//in.close();


void ClientClass::ReceiveMessages(DefaultIO* ServerSocket,string OutputFile) {
    this -> Socket = ServerSocket;
    ofstream pr(OutputFile);
    string input = "0";
    string respond ="0";
    ifstream in("input.txt");
    while(input != "8"){
  
        //cout << "First line of the loop " << endl;
        //cout << "Client call PrintMenu()" << endl;
        PrintMenu();
        //cout << "Check input before using getline: " << input << endl;
        //cout << "Finsish Reading Menu and now waiting for input from the user: " << endl;
        //getline(cin, input);
        cin >> input;
        //cout << "Check input after doing complicated if: " << input << endl;
        Socket -> write(input+'\n');

        // Execute command uploadCSVV
        if (input == "1"){
            
            //cout << "Respond is: " << respond << endl;
            respond = Socket -> read();
            //cout << "Respond after socket reading is: " << respond << endl;
            // if the respond is invalid we want to print again the menu
            if (respond == "invalid input") {
                cout << respond << endl;
                continue;
            }
            //cout << "We are in statement when input == 1 \n";
            //cout << "Reading response from the server " << endl;
            cout << respond; // "Please upload your local train CSV file.\n"
            string path;
            cin >> path;
            bool ValidFilePath = InCheck.ValidFilePath(path);
            //cout << " bool ValidFilePath = " << ValidFilePath << endl;
            if (!ValidFilePath) {
                // Send to the server to go back the the menu;
                Socket -> write("invalid input\n");
                cout << "invalid input\n";
                continue;
            }
            bool ValidFilesContent = InterfaceSendFile(path);
            //cout << "InterfaceSendFile is = " << ValidFilesContent << endl;;
            if (!ValidFilesContent) {
                Socket -> write("invalid input\n");
                cout << "invalid input\n";
                continue;
            }
        }
        if (input == "2") {
            string UserSettingInput ="0";   
            string UserMetric = "0"; 
            string UserK = "0";
            // Read corrent k from the user.
            string CorrentK = Socket -> read();
            cout << CorrentK << endl;
            // Read corrent mertic from the user.
            string CorrentMetric = Socket -> read();
            cout << CorrentMetric << endl;
            cout << "The current KNN parameters are: K = " << CorrentK << ", distance metric = " << CorrentMetric << endl;
            cin.ignore();
            getline(cin, UserSettingInput);
            cout << "UserSettingInput is: " << UserSettingInput << endl;
            istringstream is(UserSettingInput);
            is >> UserK;
            cout << "UserK = " << UserK << endl;
            is >> UserMetric;
            cout << "UserMetric = " << UserMetric << endl;
            // if (UserSettingInput == "0" || UserMetric == "0" || UserK =="0") {
            //     // Send the server that he need to go back to CLI to send the client the menu
            //     cout << "invalid value for K" << endl << "invalid value for metric" <<endl;
            //     Socket -> write(UserK+ " " + UserMetric+'\n');
            //     continue;            
            // } else {
            //     // Send the server the setting the user wants; "<K> <metric>"
            //     Socket -> write(UserK+ " " +UserMetric+'\n');        
            // }
            // // Send the server the setting the user wants; "<K> <metric>"
            Socket -> write(UserK+ " " +UserMetric+'\n');
            // Catch errors from the server.
            // Catch if both of the arguments are invalid
            string ServerCheck = Socket -> read();
            if (ServerCheck == "invalid_k_metric"){
                cout << "invalid value for K" << endl << "invalid value for metric" <<endl;
            }
            else if (ServerCheck == "invalid_k"){
                cout << "invalid value for K" << endl;
            }
            else if (ServerCheck == "invalid_metric"){
                cout << "invalid value for metric" << endl;
            }
            continue;
        }
        if (input == "3") {
            // Reading from the server if the clasifying was successfull complete or not
            string done = Socket -> read();
            cout << done << endl;
        }
    }

    pr.close();
}



void ClientClass::PrintMenu(){
    bool FlagFinishReading=false;
    while(!FlagFinishReading){
        // read string line
        string RowInMenu = Socket -> read();
        cout << RowInMenu << endl;
        if(RowInMenu == "8.exit")
            FlagFinishReading = true;
    }

}




/*void ClientClass::ClientInteraction(int ServerSocket, string OutputFile) {
    ofstream out(OutputFile);
    ifstream in("input.csv");
    string input = "";
    while (input != "6") {
        readMenue(out, ServerSocket);
        getline(in, input);
        writeStr(input, ServerSocket);
        if (input == "1") {
            out << readStr(ServerSocket) << endl; // please upload...
            while (input != "done") {
                getline(in, input);
                writeStr(input, ServerSocket);
            }
            out << readStr(ServerSocket) << endl; // Upload complete
            out << readStr(ServerSocket) << endl; // please upload...
            input = "";
            while (input != "done") {
                getline(in, input);
                writeStr(input, ServerSocket);
            }
            out << readStr(ServerSocket) << endl; // Upload complete
        }
    }
}*/
/*        if(input=="3"){
            out<<readStr(serverFD)<<endl; // Anomaly... complete
        }
        if(input=="5"){
            out<<readStr(serverFD)<<endl; // please upload...
            while(input!="done"){
                getline(in,input);
                writeStr(input,serverFD);
            }
            out<<readStr(serverFD)<<endl; // Upload complete
            out<<readStr(serverFD)<<endl; // TPR
            out<<readStr(serverFD)<<endl; // FPR
        }
    }
    in.close();
    out.close();

    close(serverFD);
    cout<<"end of client 2"<<endl;

}*/

/*    // ******************************************************************************
    // Continuously request input vectors to send to the server, until the input '-1' is received.
    InputCheck InCheck;
    while (true) {
        // Receives user input: "vector distance k".
        string UserInput;
        UserInput.clear();

        // If the user input is -1, close the connection and exit the program.
        getline(cin, UserInput);
        if(UserInput == "-1") {
            // Close socket
            close(sock);
            exit(1);
        }

        // If the message is invalid, print an 'invalid input' message to the user and prompt them for another input.
        bool ValidMessage = InCheck.ValidClientMessage(UserInput);
        if (!ValidMessage){
            cerr <<"invalid input" << endl;
            continue;
        }

        // Converts the message string into a pointer to an array of characters.
        int DataLen = UserInput.size();
        const char* message = UserInput.c_str();

        // If the number of bytes sent is less than zero, it means that the send function was unable to send the
        // message and an error has occurred.
        int SentBytes = send(sock, message, DataLen, 0);
        if (SentBytes < 0) {
            cerr << "Error: We encountered an error while trying to send your message, please try again later. ";
            close(sock);
            exit(1);
        }

        // Receive a response from the server and clear the contents of the buffer.
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        int ExpectedDataLen = sizeof(buffer);
        int ReadBytes = recv(sock, buffer, ExpectedDataLen, 0);

        // If the number of bytes received is zero, close the connection with the server.
        if (ReadBytes == 0) {
            cerr << "Connection with the server closed ";
            close(sock);
            exit(0);
        }

            // If the number of bytes received is a negative number, than an error occurred while reading the response.
        else if (ReadBytes < 0) {
            cerr << "Error: An error occurred while reading the response from the server. Please try again later.";
            close(sock);
            exit(1);
        }
            // Print the message received from the server.
        else {
            cout << buffer << endl;
        }
    }*/
    // ******************************************************************************
