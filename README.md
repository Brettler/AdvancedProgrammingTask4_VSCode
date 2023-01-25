# AdvancedProgrammingTask4_VSCode
Eden Berman &amp; Liad Brettler

# Description:
In this program, we created a server and client and established a connection between them. The client sends the server an unclassified vector received from the user, and the server runs the KNN algorithm on the vector and returns the result to the client to be displayed to the user. The client runs in an infinite loop, waiting for the next user input. The user can close the client by typing '-1', which will close the connection to the server and then shut down the program. However, the server remains active and listens for the next client to request a connection. As long as a client is connected to the server, the server will listen for new requests.

The server is provided with a database in the form of a CSV file. To calculate the distances between the sample and the entire database, the KNN algorithm will use one of the distance metrics implemented in Task 1: Euclidean, Manhattan, Chebyshev, Canberra, or Minkowski.

# Compile & Run Instructions:
Run the following commands:
* git init
* git clone https://github.com/Brettler/AdvancedProgrammingTask3.git
* cd 'path' - for example: /u/students/brettll1/AdvancedProgrammingTask3
* make

To start the server, enter the following command and arguments in this order: *./server.out 'file_path' 'port'.*

In a separate terminal, start the client by entering the following command and arguments in this order: *./client.out 'IP_address' 'port'.*

Note: the 'port' value must be the same for the server and client.

* Creating the server and the client using the command ./server.out or ./client.out respectively.
* 'file_path' - The path of the file containing the classified data.
* 'port' - The port number the server listens on and establishes a connection with a client through.
* 'IP_address' - The IPv4 address of the server the client wishes to connect to.

Next, the user may input the information for the sample they wish to classify: 'vector' 'distance_metric' 'k_value'. The program will then display the classification of the sample, or an error message if an invalid input was received. The user may continue to input new samples as described above, or terminate the program by typing '-1'.

# Invalid Input:
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

Each class has a header file that declares its member & function declarations, lists the necessary imported libraries, and includes the required headers.
