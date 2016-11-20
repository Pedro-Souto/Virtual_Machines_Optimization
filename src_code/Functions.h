#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "Classes.h"
#include <z3++.h>

using namespace z3;
using namespace std;

void split(const string &s, char delim, vector <string> &elems);
void modelo_VM(vector<Server> sortedServers, vector <VM> VMList, int reqServers,vector <vector <int> > listaTrues);
expr mk_add(expr_vector args);
