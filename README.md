# AdvancedProgrammingTask4_VSCode
Eden Berman &amp; Liad Brettler

# Description:
In this program, we created a server and a client that communicate using a Command Line Interface (CLI). The program utilizes the Command design pattern, which separates actions from the object itself by encapsulating them in separate command objects, providing greater flexibility in managing and controlling actions. Multiple clients can connect to the server simultaneously, each through a separate socket, and submit requests to execute the KNN classification algorithm. Once connected, the client is presented with a menu of options including the following:
1. Uploading classified and unclassified CSV files for train and test sets respectively.
2. Configuring K value and distance metric for the KNN algorithm settings.
3. Classifying test set using the KNN algorithm.
4. Displaying classification results.
5. Downloading classification results locally.
8. Exiting the program.

Each action is implemented using an execution method in the CLI, verification methods in both the server and client, and socket-based input/output communication. The server remains active and listens continuously for new client connections, and as long as a client is connected, the server will process requests.

# Compile & Run Instructions:---
Run the following commands:
* git init
* git clone https://github.com/Brettler/AdvancedProgrammingTask4_VSCode.git
* cd 'path' - for example: /u/students/brettll1/AdvancedProgrammingTask4_VSCode.git
* make

To start the server, enter the following command and arguments in this order: *./server.out 'file_path' 'port'.*

In a separate terminal, start the client by entering the following command and arguments in this order: *./client.out 'IP_address' 'port'.*

Note: the 'port' value must be the same for the server and client.

* Creating the server and the client using the command ./server.out or ./client.out respectively.
* 'file_path' - The path of the file containing the classified data.
* 'port' - The port number the server listens on and establishes a connection with a client through.
* 'IP_address' - The IPv4 address of the server the client wishes to connect to.

Next, the user may input the information for the sample they wish to classify: 'vector' 'distance_metric' 'k_value'. The program will then display the classification of the sample, or an error message if an invalid input was received. The user may continue to input new samples as described above, or terminate the program by typing '-1'.

# Invalid Input:---
This program processes a CSV file containing classified samples. Each row represents a single sample, with all columns containing 'double' values except for the last column, which should contain the classification name.

If the program encounters invalid inputs during the initialization of the server or the client, it will terminate. If it receives invalid inputs from the user or the file, it will display an error message. Invalid inputs include an empty or corrupted file, an incorrect file path, a file with whitespace characters between vector values, and values that cannot be converted to the appropriate data type ('double', 'int', etc).

_Warning:_ This program only supports CSV files. The presence of any whitespace characters within a vector will cause the program to terminate. Please take this into consideration.

# Classes:
* Server - The main function in this class runs the server by following a specific logical order. It receives two arguments: a file name or path, and a port number. These arguments are then checked for validity. Next, the server is created and initiated in this function.

* Client - The main function in this class runs the client by following a specific logical order. It receives two arguments: an IP address and a port number. These arguments are then checked for validity. Next, the client is created and initiated in this function.

* ServerClass - This class receives a map of data and a port number to establish a connection with a client. The 'run' function sets up a socket and a port, and attempts to connect them. The server listens for incoming clients and maintains a queue of up to five clients. When a client connects, the server can continuously process their requests, sending back a response such as a label calculated by using the KNN algorithm, or a message indicating invalid input.

* ClientClass - This class establishes a connection with a server using an IP address and a port number. The run function initializes a socket, sets the IP address and port, and creates the connection. It then prompts the user for input containing a vector, metric, and k value, and validates the arguments received. The client sends the validated message to the server and waits for a response. If an error occurs while sending the message, the socket is closed and the program exits. If everything is successful, the client displays the label received from the server or an error message to the user. The client remains in a loop, continuously waiting for the user's next input. To terminate the client, the user can enter '-1', which will close the client but not the server.

* DataImport - This class receives the name of a CSV file and attempts to open it. If the file is not empty, it processes each row as a sample, placing the numeric values into a vector representing the key, and placing the classification name into a string representing the value in a map. While generating the map, it ensures that all vectors are of the same size and eliminates duplicates.

* DistanceCalc - This section contains functions to calculate various distance metrics: Euclidean, Manhattan, Chebyshev, Canberra, and Minkowski. Each metric has its own function that takes two vectors as input and calculates the distance between them. The Euclidean and Manhattan functions are implemented using the Minkowski function with P values of 2 and 1, respectively. The Minkowski function uses a default P value of 2.

  Note: we treated '.2' as '0.2', and '2.' as '2.0', based on the operation of the generic calculator.

* InputCheck - This class validates all input to ensure the program runs smoothly. If any validation check fails, the program will either terminate or send an error message. The user input is validated by checking the K value, file path, metric name, and numeric vector inputs. It also performs file checks like verifying the file name, checking for empty files, and the existance of whitespace characters. In addition, it checks for matching vector sizes, and converts string vectors to double vectors. It validates the client properties such as the client message, port number, and IP address.

* KNN - This class performs the main task of the program. It takes in the K value, a map of data, a distance metric, and a vector as input. It first calculates the distances between the input vector and all samples in the data map using the provided distance metric. It stores all distance-label pairs in a multimap, which automatically sorts them in ascending order. This means that the samples with the shortest distance to the input vector will be at the beginning of the multimap. It then selects the K labels at the beginning of the multimap and places them in a vector of strings. These K labels correspond to the K nearest neighbors. Finally, it predicts the label of the input vector based on the most common label among the K nearest neighbors.

* CLI - This class is designed to handle the communication and execution of commands between a client and the server. It is instantiated for each client that connects to the server using an instance of DefaultIO, and creating an instance of SharedData. It also contains a list of available commands that can be executed by the client in a command vector. The class greets the client with the server's welcome menu and handles the client's command selections.

* Command - This class serves as a base for all command classes, and each derived class overrides the execute method to perform a specific action. It takes in an instance of DefaultIO and SharedData from each derived class to access necessary information for execution.

* CommandUploadCSV - This command class allows the user to upload two types of files to the server, a classified data file and an unclassified data file. It verifies the validity of each file before uploading it. If a file is determined to be valid, it sets the appropriate classified or unclassified data in the SharedData object and returns the message "Upload complete." If the file is invalid, it returns the message "Invalid input." The command processes each row of the file individually and stores it in a new file on the server. The welcome menu will be displayed once again after this.

* CommandSettingsKNN - This command class enables the user to configure the settings of the KNN model. The default settings are K = 5 and metric = "AUC". If the user desires to change these values, they can enter new values in the specified order. These values will be updated in the SharedData object. If the user presses 'Enter' without entering new values, the current settings will be retained. Any invalid input will result in the server returning the message "Invalid input" and the current settings will remain unchanged. The welcome menu will be displayed once again after this.

* CommandClassify - This command class allows the user to run the KNN algorithm using a classified data file as the training set and an unclassified data file as the test set, utilizing the KNN settings saved in the SharedData object. Upon completion, the classified results will be stored in the appropriate vector of the SharedData object and the message "classifying data complete" will be returned. If data has not been uploaded prior to calling this command, the classification will not take place and the message "please upload data" will be returned. The welcome menu will be displayed once again after this.

* CommandDisplay - This command class presents the user with the results of data classification performed by the KNN algorithm. This displayed in the format of 'index number' 'label' on separate rows for each classification result. Finally, the message "done" will be displayed on a separate line. If data files have not been uploaded prior, the server will display the message "please upload data". If the data has not yet been classified, the server will display the message "please classify the data". The welcome menu will be displayed once again after this.

* CommandDownload - This command class enables the user to download a file locally containing the classification results, presented in the format of 'index number' 'label' on separate rows for each classification result. The user inputs a path to the desired location to download the file and the server sends the necessary information to the client to create the file. If data files have not been uploaded prior, the server will display the message "please upload data". If the data has not yet been classified, the server will display the message "please classify the data". The welcome menu will be displayed immediately, regardless of whether the file download has completed or not.

  Note: The server automatically names the results file as 'ResultsFile_X_Y.csv' and prompts the user to specify the desired file path for the download, but does not           allow the user to name the file prior to downloading.

* CommandExit - This command class allows the user to terminate the connection with the server.

* SharedData - This class houses all the information required for various commands to execute correctly. This information includes the algorithm settings k and metric, a map of the classified data file, a vector of the unclassified data file, a vector containing the classification results, and the client socket number. Each member has a corresponding get and set method, allowing all commands to access and update the SharedData object as necessary.

* DefaultIO - This class serves as the foundation for input and output, and is the foundation for communication between the server and the client. Derived classes will override the implementation of the read and write methods.

* SocketIO - This class is derived from the DefaultIO base class, it receives a socket number associated with each client, and facilitates communication between that client and the server. It overrides the read and write methods and implements them using string messages.

Each class has a header file that declares its member & function declarations, lists the necessary imported libraries, and includes the required headers.
