// Eden Berman 318530474
// Liad Brettler 318517182

#include "ServerClass.h"

// Constructor
// :DataMap(DataMap) - this format receives the const arguments by reference.
ServerClass::ServerClass(int ServerPort)
        :ServerPort(ServerPort)  {}

void ServerClass::run() const {

    // Initialize a socket.
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
        exit(1);
    }

    // Configure the IP address and port.
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(ServerPort);

    // Bind the socket to the IP address and port.
    if (bind(sock,(struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding socket");
        exit(1);
    }


    // Listen for incoming connections. Up to five clients at a time.
    while(true) {
        if (listen(sock, 5) < 0) {
            perror("error listening to a socket");
            exit(1);
        }
        // Accept connection from a client.
        struct sockaddr_in client_sin;
        unsigned int addr_len = sizeof(client_sin);
        int ClientSock = accept(sock, (struct sockaddr *) &client_sin, &addr_len);
        if (ClientSock < 0) {
            perror("error accepting client");
            exit(1);
        }

        SocketIO SockOBJ(ClientSock);
        CLI cli(&SockOBJ);

        cli.start();

        










/*        // Read the data from the client
        while (true) {
            string ServerResponseMessage;
            char buffer[4096];
            memset(buffer, 0, sizeof(buffer));
            int expected_data_len = sizeof(buffer);
            int ReadBytes = recv(ClientSock, buffer, expected_data_len, 0);

            // If the number of bytes received is zero, close the connection with the server.
            if (ReadBytes == 0) {
                cout << "Connection with the client is closed" << endl;
                break;
            } else if (ReadBytes < 0) {
                // If the number of bytes received is a negative number, an error occurred while reading the response.
                cerr << "Error reading data from the client" << endl;
                break;
            }

            else {
                // CreatResponseMessage will return "invalid input" if the input is invalid.
                // Otherwise, will return a prediction from the KNN algorithm.
                ServerResponseMessage = CreatResponseMessage(ServerResponseMessage, buffer);
            }

            // Convert the server message (error or prediction) from a string to an array of chars.
            const char* BufferPrediction = ServerResponseMessage.c_str();
            int ResponseSize = ServerResponseMessage.size();

            // Send response to the client.
            int SentBytes = send(ClientSock, BufferPrediction, ResponseSize, 0);
            if (SentBytes < 0) {
                perror("error sending to client");
                break;
            }
        }*/
    }
}

/*
// Returns the classification type or an error message accordingly.
string ServerClass::CreatResponseMessage(string ServerResponseMessage, char buffer[]) const {
    InputCheck InCheck;
    vector<string> vec;
    string SingleString;

    string StringInput(buffer);
    istringstream is(StringInput);

    vector<double> DoubleVector;
    string metric;
    string KString;

    // Read the vector values
    while (is >> StringInput) {

        try {
            stod(StringInput);
            // If the conversion from string to double using 'stod' is successful, we will perform additional checks to
            // catch edge cases such as "12abc", which 'stod' will convert without an issue, but is an invalid value.
            bool ValidVector = InCheck.ValidDoubleVector(StringInput);
            if (ValidVector) {
                DoubleVector.push_back(stod(StringInput));
            }
            else {
                // If the input is not a valid number, it must be a distance measurement.
                metric = StringInput;
                break;
            }
        }
        catch (exception& invalid_value) {
            // If the input is not a valid number, it must be a distance measurement.
            metric = StringInput;
            break;
        }
    }

    // Read and validate the k value.
    is >> KString;
    int k = InCheck.ValidKNumber(KString);
    // Validate the metric.
    bool ValidMetric = InCheck.ValidDistanceMetric(metric);

    // Extract the first vector from the data map to compare its size to the user input vector.
    map<vector<double>, string>::const_iterator p = DataMap.begin();

    // Dereference the iterator to get the key-value pair, and access the key of the pair.
    pair<vector<double>, string> kv = *p;
    vector<double> FirstKey = kv.first;

    // Compare the user input vector size to the first vector in the map.
    bool ValidVectorSize = InCheck.ValidVectorSizeCheck(FirstKey, DoubleVector);

    // If any of the checks fail, we will send an "invalid input" message back to the client to display it.
    if(k == -1 || k > DataMap.size() || !ValidMetric || !ValidVectorSize) {
        ServerResponseMessage = "invalid input";
    }
    else {
        // Implementing the KNN algorithm.
        KNN knn(k, DataMap, metric, DoubleVector);
        ServerResponseMessage = knn.predict();
    }
    return ServerResponseMessage;
}*/
