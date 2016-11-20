#pragma once

#include "Classes.h"
#include "Functions.h"

using namespace std;

class importTXT {
public:
	string _filepath = "";
	int _numServers=0;
	int _numVirtual=0;
	vector<VM> _VMList;
	vector<Server> _serverList;

	importTXT();
	importTXT(string filepath);

	void readFile();

};