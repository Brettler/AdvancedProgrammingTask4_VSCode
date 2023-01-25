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
    cout << "Sock numer is: " << sock << endl;
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
    this -> SocketNum = sock;
    return sock;
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


void ClientClass::ReceiveMessages(DefaultIO* ServerSocket) {
    this -> Socket = ServerSocket;
    string input = "0";
    string respond ="0";
    ifstream in("input.txt");
    while(input != "8"){
  
        PrintMenu();
        // Getting user's choice which command he wants.
        cin >> input;
        //cout << "Check input after doing complicated if: " << input << endl;
        Socket -> write(input+'\n');

        // Execute command uploadCSVV
        if (input == "1"){
            
            respond = Socket -> read();

            // if the respond is invalid we want to print again the menu
            if (respond == "invalid input") {
                cout << respond << endl;
                continue;
            }
            // "Please upload your local train CSV file.\n"
            cout << respond; 
            string path;
            cin >> path;
            bool ValidFilePath = InCheck.ValidFilePath(path);
   
            if (!ValidFilePath) {
                // Send to the server to go back the the menu;
                Socket -> write("invalid input\n");
                cout << "invalid input\n";
                continue;
            }
            bool ValidFilesContent = InterfaceSendFile(path);

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
            
            // Recive the new setting from the user
            cin.ignore();
            getline(cin, UserSettingInput);
            
            // Split the string of information <k> <metric>
            istringstream is(UserSettingInput);
            is >> UserK;
            cout << "UserK = " << UserK << endl;
            is >> UserMetric;
            cout << "UserMetric = " << UserMetric << endl;
            // Send to the server user choice as one string.
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
        if (input == "4") {
            string label = Socket -> read();
            if (label == "please classify the data" || label == "please upload data") {
                cout << label << endl;
                continue;
            } else {
                cout << label << endl;
            }
            
            // Printing for the user the index and label. 
            while (label != "Done.") {
                label = Socket -> read();      
                cout << label << endl;
            }
        }
        if (input == "5") {
            
        }
    }
}

void ClientClass::PrintMenu(){
    bool FlagFinishReading=false;
    while(!FlagFinishReading){
        // read string line
        string RowInMenu = Socket -> read();
        cout << RowInMenu << endl;
        if(RowInMenu == "8. exit")
            FlagFinishReading = true;
    }

}

bool ClientClass::InterfaceSendFile (string& path) {
    string row;
    ifstream FileCSV(path);
    // Reading each row in the file
    while (getline(FileCSV, row)){
        Socket->write(row + "\n");

    }

    // We will add 'end-of-message' marker to know when we finished reading the messege
    Socket->write("//EOM_MARKER\n");
    FileCSV.close();

    // the client will read: upload complete / invalid input
    string response = Socket->read(); 
    cout << response << endl;
    if (response == "invalid input") {
        return false;
    }
    
    // the client will read: "Please enter the path to the test file:
    response = Socket -> read(); 
    cout << response << endl;
    string TestPath;
    cin >> TestPath;
    // Check if the path to the test file is valid, if not valaid we will return false;
    bool ValidFilePath = InCheck.ValidFilePath(TestPath);
    if (!ValidFilePath){
        return false;
    }

    // Send the contents of the file to the server, row by row
    ifstream TestCSV(TestPath);
    while (getline(TestCSV, row)){
        Socket->write(row + "\n");

    }
    // We will add 'end-of-message' marker to know when we finished reading the messege
    Socket->write("//EOM_MARKER\n");
    TestCSV.close();

    // the client will read: upload complete / invalid input
    response = Socket->read(); 
    if (response == "invalid input") {
        return false;
    } else {
        // Upload Complete
        cout << response << endl; 
    }
    return true;
}

void ClientClass::DownloadFile(){
        string row;
        string StatusReport = Socket -> read();
        if (StatusReport == "please classify the data" || StatusReport == "please upload data") {
            cout << StatusReport << endl;
            continue;
        } else {
            InputCheck ic;
            // Getting path from the user
            string PathDownload;
            cin >> PathDownload; 
            string FullPath = PathDownload + "/ResultsFile_" +to_string(this-> SocketNum) + "_" + to_string(counter) +".csv";
            
            cout << "Full path is: " << FullPath << endl;
            ofstream ResultsFile(FullPath, ios::out | ios::trunc);
            // Check if valid path given
            bool ValidPath = ic.ValidFilePath(FullPath);
            if (!ValidPath) {
                cout << "invalid input\n";
                Socket -> write("err_exp\n");
                continue;
            }
            else {
                Socket -> write("good\n");
            }
            // Printing for the user the index and label.
            row = Socket -> read(); 
            do {
                ResultsFile << row << endl;
                row = Socket -> read();
                // We clean the whitspace in the last row
                if (row == "Done.") {
                    // need to handl last line as a whitespaces;
                }
            } while(row != "Done.");
            //ResultsFile.close();
            this -> counter++;
        }
}
