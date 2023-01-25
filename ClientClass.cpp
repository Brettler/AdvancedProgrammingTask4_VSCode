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



//  void ClientClass::SendMessages(DefaultIO* ServerSocket) {
//         this -> Socket = ServerSocket;
//      //unique_lock<mutex> lock(mtx);
//         string row;
//         ofstream ResultsFile(FullPathOyler, ios::out | ios::trunc);
//         // Saving for the user the index and label.
//         row = Socket -> read(); 
//         do {
//             ResultsFile << row << endl;
//             row = Socket -> read();
//             // We clean the whitspace in the last row
//             if (row == "Done.") {
//                 // need to handl last line as a whitespaces;
//             }
//         } while(row != "Done.");
//         //ResultsFile.close();
//         this -> counter++;
//         //lock.unlock();
//  }



void ClientClass::ReceiveMessages(DefaultIO* ServerSocket) {
    this -> Socket = ServerSocket;
    string input = "0";
    string respond ="0";
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
            cout << respond << endl; 
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
            is >> UserMetric;
       
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

        // Execute command 3 aka callasify the data
        if (input == "3") {
            // Reading from the server if the clasifying was successfull complete or not
            string done = Socket -> read();
            cout << done << endl;
        }

        // Execute command 4 aka display the results to the user
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
            // Waiting for the user to press enter, when he does we continue
            string enter;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }

        // Execute command 5 aka download.
        if (input == "5") {
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
                ofstream ResultsFile(FullPath, ios::out | ios::trunc);
                cout << "Path is " << FullPath << endl;
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

                //this -> FullPathOyler = FullPath;
                //this -> PerfectPath =FullPath;
                ResultsFile.close();
                //DownloadFile(&ResultsFile);
                //thread download(&ClientClass::DownloadFile, this, FullPath);
                // This will run the thread in the background and allow the program to continue executing
                //download.detach();
                DownloadFile(FullPath);
               
                
            }
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

void ClientClass::DownloadFile(string path){
    
    //cout << "We are in downloadfile functionn\n";
    //unique_lock<mutex> lock(mtx);
    ofstream ResultsFile(path, ios::out | ios::trunc);
    string row;
    // Saving for the user the index and label.
    row = Socket -> read(); 
    do {
        //cout << "We are in the do while looop\n";
        ResultsFile << row << endl;
        row = Socket -> read();
        // We clean the whitspace in the last row
        if (row == "Done.") {
            cout << "We are in if done\n";

            // need to handl last line as a whitespaces;
        }
    } while(row != "Done.");
    //ResultsFile.close();
    //cout << "Finished the while done loop\n";

    this -> counter++;
    //lock.unlock();
}
