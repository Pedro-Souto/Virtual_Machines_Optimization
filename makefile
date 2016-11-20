CFLAGS = -Wall -g -pedantic -lm -std=c++11 -lz3
FOLDER = src_code/
CC = g++
PROJNAME = proj2
current_dir = $(shell pwd)
Z3_DIR= $(current_dir)/z3
INC_DIR = $(Z3_DIR)/include/
LIB_DIR = $(Z3_DIR)/bin/

$(PROJNAME): List.o Node.o Server.o VM.o importTXT.o Functions.o main.o
	$(CC) $(CFLAGS) -I$(INC_DIR) -o $(PROJNAME) List.o Node.o Server.o VM.o importTXT.o Functions.o main.o $(LIB_DIR)libz3.so

Functions.o: $(FOLDER)Functions.cpp $(FOLDER)Functions.h $(FOLDER)Classes.h $(FOLDER)List.h
	$(CC) $(CFLAGS) -c $(FOLDER)Functions.cpp

List.o: $(FOLDER)List.cpp $(FOLDER)List.h $(FOLDER)importTXT.h $(FOLDER)Classes.h
	$(CC) $(CFLAGS) -c $(FOLDER)List.cpp

Server.o: $(FOLDER)Server.cpp $(FOLDER)Classes.h
	$(CC) $(CFLAGS) -c $(FOLDER)Server.cpp

Node.o: $(FOLDER)Node.cpp $(FOLDER)Classes.h
	$(CC) $(CFLAGS) -c $(FOLDER)Node.cpp

VM.o: $(FOLDER)VM.cpp $(FOLDER)Classes.h
	$(CC) $(CFLAGS) -c $(FOLDER)VM.cpp

importTXT.o: $(FOLDER)importTXT.cpp $(FOLDER)importTXT.h $(FOLDER)Classes.h $(FOLDER)Functions.h
	$(CC) $(CFLAGS) -c $(FOLDER)importTXT.cpp

main.o: $(FOLDER)main.cpp $(FOLDER)List.h $(FOLDER)importTXT.h $(FOLDER)Functions.h
	$(CC) $(CFLAGS) -c $(FOLDER)main.cpp -o main.o

clean:
	rm -f *.o $(PROJNAME)

zip: clean
	rm -f $(PROJNAME).zip
	zip   $(PROJNAME).zip *

run:
	find $(current_dir)/Testes -maxdepth 3 -type f -exec ./$(PROJNAME) {} \;
