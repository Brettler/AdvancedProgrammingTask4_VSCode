OBJS	= DataImport.o DistanceCalc.o InputCheck.o KNN.o Server.o ServerClass.o CLI.o Command.o CommandUploadCSV.o SharedData.o DefaultIO.o SocketIO.o Client.o ClientClass.o
OUT	= myproject1,myproject2

OBJS0	= DataImport.o DistanceCalc.o InputCheck.o KNN.o Server.o ServerClass.o CLI.o Command.o CommandUploadCSV.o SharedData.o DefaultIO.o SocketIO.o
SOURCE0	= DataImport.cpp DistanceCalc.cpp InputCheck.cpp KNN.cpp Server.cpp ServerClass.cpp CLI.cpp Command.cpp CommandUploadCSV.cpp SharedData.cpp DefaultIO.cpp SocketIO.cpp
HEADER0	= DataImport.h DistanceCalc.h InputCheck.h KNN.h Server.h ServerClass.h CLI.h Command.h SharedData.h DefaultIO.h
OUT0	= myproject1

OBJS1	= DataImport.o DistanceCalc.o InputCheck.o KNN.o Client.o ClientClass.o CLI.o Command.o CommandUploadCSV.o SharedData.o
SOURCE1	= DataImport.cpp DistanceCalc.cpp InputCheck.cpp KNN.cpp Client.cpp ClientClass.cpp CLI.cpp Command.cpp CommandUploadCSV.cpp SharedData.cpp
HEADER1	= DataImport.h DistanceCalc.h InputCheck.h KNN.h Client.h ClientClass.h CLI.h Command.h
OUT1	= myproject2

CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -lpthread

all: server.out client.out

server.out: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

client.out: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

DataImport.o: DataImport.cpp
	$(CC) $(FLAGS) DataImport.cpp -std=c11

DistanceCalc.o: DistanceCalc.cpp
	$(CC) $(FLAGS) DistanceCalc.cpp -std=c11

InputCheck.o: InputCheck.cpp
	$(CC) $(FLAGS) InputCheck.cpp -std=c11

KNN.o: KNN.cpp
	$(CC) $(FLAGS) KNN.cpp -std=c11

Server.o: Server.cpp
	$(CC) $(FLAGS) Server.cpp -std=c11

ServerClass.o: ServerClass.cpp
	$(CC) $(FLAGS) ServerClass.cpp -std=c11

CLI.o: CLI.cpp
	$(CC) $(FLAGS) CLI.cpp -std=c11

Command.o: Command.cpp
	$(CC) $(FLAGS) Command.cpp -std=c11

CommandUploadCSV.o: CommandUploadCSV.cpp
	$(CC) $(FLAGS) CommandUploadCSV.cpp -std=c11

SharedData.o: SharedData.cpp
	$(CC) $(FLAGS) SharedData.cpp -std=c11

DefaultIO.o: DefaultIO.cpp
	$(CC) $(FLAGS) DefaultIO.cpp -std=c11

SocketIO.o: SocketIO.cpp,
	$(CC) $(FLAGS) SocketIO.cpp, -std=c11

Client.o: Client.cpp
	$(CC) $(FLAGS) Client.cpp -std=c11

ClientClass.o: ClientClass.cpp
	$(CC) $(FLAGS) ClientClass.cpp -std=c11


clean:
	rm -f $(OBJS) $(OUT)
