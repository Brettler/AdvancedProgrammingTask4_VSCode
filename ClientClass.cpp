// Eden Berman 318530474
// Liad Brettler 318517182

#include "ClientClass.h"

// Constructor:
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

// Execute commands according to user inputs.
void ClientClass::ReceiveMessages(DefaultIO* ServerSocket) {
    this -> Socket = ServerSocket;
    string input = "0";
    string respond = "0";
    
    // Command executer.
    do {
        bool FlagEnter = false;
        PrintMenu();
        // Receiving user's command choice.
        cin >> input;
        Socket -> write(input +'\n');

        // Execute command UploadCSV.
        if (input == "1") {
            respond = Socket -> read();

            // Display massage for invalid input.
            if (respond == "invalid input") {
                cout << respond << endl;
                continue;
            }

            // Otherwise, the response message will be: "Please upload your local train CSV file.\n"
            cout << respond << endl; 
            string path;
            cin >> path;

            // Messages server to return to the options menu if invalid input.
            bool ValidFilePath = InCheck.ValidFilePath(path);
            if (!ValidFilePath) {
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
            continue;
        }

        // Execute CommandSettingsKNN.
        if (input == "2") {
            SettingKNN(this -> Socket);
            continue;
        }

        // Execute CommandClassify.
        if (input == "3") {
            // Receiving server message whether classifying complete or an error occured.
            string done = Socket -> read();
            cout << done << endl;
            continue;
        }

        // Execute CommandDisplay.
        if (input == "4") {
            string label = Socket -> read();

            // Verify the appropriate actions were taken prior.
            if (label == "please classify the data" || label == "please upload data") {
                cout << label << endl;
                continue;
            } else {
                cout << label << endl;
            }
            
            // Displaying to the user the index and adjacent to the classification label. 
            while (label != "Done.") {
                label = Socket -> read();      
                cout << label << endl;
            }

            // Waiting for the user to press enter, when he does we continue.
            string enter;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            continue;
        }

        // Execute CommandDownload.
        if (input == "5") {
            string StatusReport = Socket -> read();

            // Verify the appropriate actions were taken prior.
            if (StatusReport == "please classify the data" || StatusReport == "please upload data") {
                cout << StatusReport << endl;
                continue;

            // Begin the downloading process once the action is cleared for takeoff.
            } else {
                InputCheck ic;

                // Receiving a path from the user.
                string PathDownload;
                cin >> PathDownload; 
                srand (time(nullptr));
                int rand = std::rand();
                string FullPath = PathDownload + "/ResultsFile_" + to_string(rand) + "_" + to_string(counter) + ".csv";
                this -> counter++;
                ofstream ResultsFile(FullPath, ios::out | ios::trunc);

                bool ValidPath = ic.ValidFilePath(FullPath);
                if (!ValidPath) {
                    cout << "invalid input\n";
                    Socket -> write("err_exp\n");
                    continue;
                }
                else {
                    Socket -> write("good\n");
                }
                string row;
                // Saving the index and label for user's file.
                row = Socket -> read(); 
                do {
                    ResultsFile << row << endl;
                    row = Socket -> read();
                } while (row != "Done.");

                ResultsFile.close();
                continue;
            }
        }
    } while (input != "8");
}

// Display the menu options to the user.
void ClientClass::PrintMenu() {
    bool FlagFinishReading = false;
    while (!FlagFinishReading) {
        string RowInMenu = Socket -> read();
        cout << RowInMenu << endl;
        if (RowInMenu == "8. exit")
            FlagFinishReading = true;
    }
}

// Sending the file contents to the server.
bool ClientClass::InterfaceSendFile (string& path) {
    string row;
    ifstream FileCSV(path);

    // Reading each row of the file individually.
    while (getline(FileCSV, row)){
        Socket->write(row + "\n");
    }

    // Adding 'end-of-message' marker to know when we have reached the end of the message.
    Socket -> write("//EOM_MARKER\n");
    FileCSV.close();

    // The client will read "upload complete" or "invalid input".
    string response = Socket -> read(); 
    cout << response << endl;
    if (response == "invalid input") {
        return false;
    }
    
    // The client will read: "Please enter the path to the test file".
    response = Socket -> read(); 
    cout << response << endl;
    string TestPath;
    cin >> TestPath;

    // Check if test file path is valid.
    bool ValidFilePath = InCheck.ValidFilePath(TestPath);
    if (!ValidFilePath) {
        return false;
    }

    // Send the contents of the file to the server one row at a time.
    ifstream TestCSV(TestPath);
    while (getline(TestCSV, row)) {
        Socket -> write(row + "\n");
    }

    // Adding 'end-of-message' marker to know when we have reached the end of the message.
    Socket -> write("//EOM_MARKER\n");
    TestCSV.close();

    // The client will read "upload complete" or "invalid input".
    response = Socket -> read(); 
    if (response == "invalid input") {
        return false;
    } else {
        cout << "Upload complete." << endl; 
    }
    return true;
}

// Algorithm settings method for K and metric values.
void ClientClass::SettingKNN(DefaultIO* Socket) {
    string UserSettingInput;   
    string UserMetric; 
    string UserK;

    // Read current K and metric values from user and display them.
    string CurrentK = Socket -> read();
    string CurrentMetric = Socket -> read();
    cout << "The current KNN parameters are: K = " << CurrentK << ", distance metric = " << CurrentMetric << endl;
    
    // Recive the new setting from the user.
    cin.ignore();
    getline(cin, UserSettingInput);
    if (UserSettingInput == "\n") {
        return;
    }
    // Split the information string <k> <metric>
    istringstream is(UserSettingInput);
    is >> UserK;
    is >> UserMetric;
    
    // Send to the server a string of the user's choice.
    Socket -> write(UserK + " " + UserMetric + '\n');

    // Catch server errors and invalid arguments.
    string ServerCheck = Socket -> read();
    if (ServerCheck == "invalid_k_metric") {
        cout << "invalid value for K" << endl << "invalid value for metric" << endl;
    }
    else if (ServerCheck == "invalid_k") {
        cout << "invalid value for K" << endl;
    }
    else if (ServerCheck == "invalid_metric") {
        cout << "invalid value for metric" << endl;
    }
}