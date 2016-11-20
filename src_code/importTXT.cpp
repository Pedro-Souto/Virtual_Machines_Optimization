#include "importTXT.h"


importTXT::importTXT() {}

importTXT::importTXT(string filepath) { _filepath = filepath;}

void importTXT::readFile(){

	ifstream filetoread;
	int counter = 1;
	filetoread.open(_filepath);
	string line;
	vector<string> lineSplit;
	while (getline(filetoread, line)){

		split(line, ' ', lineSplit);

		if (counter == 1) {
			_numServers=stoi(lineSplit[0]);
		}
		else if (((int) lineSplit.size() == 1 && counter != 1) || (counter != 1 && (int) lineSplit.size()>1 && lineSplit[1] == "")) {
			_numVirtual= stoi(lineSplit[0]);
		}
		else if ((int) lineSplit.size()>1 && (int) lineSplit.size()<4) {
			_serverList.push_back(Server(stoi(lineSplit[0]), stoi(lineSplit[1]),stoi(lineSplit[2])));
		}
		else {
			_VMList.push_back(VM(stoi(lineSplit[0]), stoi(lineSplit[1]), stoi(lineSplit[2]), stoi(lineSplit[3]), (lineSplit[4]=="True")));
		}
		lineSplit.clear();
		counter++;
	}

		filetoread.close();
}

