#include "List.h"

List::List() {}

List::List(vector<VM> VMlist, vector<Server> serverlist) {
	_VMList = VMlist;
	_serverList = serverlist;
	_nVM = (int)VMlist.size();
	_jobList = getjobList();
	_nServers = (int) serverlist.size();
	_nJobs = (int) _jobList.size();
	_reqServers = 0;
	_sortedServerList=sortServerbyscore();

}

int List::sumRAMVMs() {
	int sumRAMVMs = 0;

	for (int i = 0; i < (int) _VMList.size(); i++) {
		sumRAMVMs += _VMList[i]._RAM;
	}
	return sumRAMVMs;
}

int List::sumCPUVMs() {
	int sumCPUVMs = 0;

	for (int i = 0; i < (int) _VMList.size(); i++) {
		sumCPUVMs += _VMList[i]._CPU;
	}
	return sumCPUVMs;
}

int List::calc_maxVMIndex() {
	vector<int> auxList;
	int s = 0;

		for (int i = 0; i < (int) _VMList.size(); i++)
		{
			if (_VMList[i]._VMindex >s)
				{s=_VMList[i]._VMindex;}
		}
	return s + 1;

}



vector<int> List::getjobList() {
	list<int> aux;

	for (int i = 0; i < (int) _VMList.size(); i++)
		aux.push_back(_VMList[i]._jobid);

	aux.sort();
	aux.unique();
	vector<int> v{ aux.begin(), aux.end() };

	return v;
}


vector<VM> List::sortVMbyjob() {
	vector<VM> sorted;
	for (int i = 0; i < (int) _jobList.size(); i++)
		for (int j = 0; j < (int) _VMList.size(); j++) {
			{
				if (_VMList[j]._jobid == _jobList[i])
					sorted.push_back(_VMList[j]);
			}
		}
	return sorted;
}

int List::getNJobsbyid(int jobid) {
	int counter = 0;

	for (int j = 0; j < (int) _VMList.size(); j++) {
		{
			if (_VMList[j]._jobid == jobid)
				counter++;
		}
	}

	return counter;
}

void List::setVarList(importTXT txtFile) {

	_varList.clear();

	int varNum = 1;
	vector<Node> aux;
	for (int c = 1; c <= _nVM; c++) {
		_varList.push_back(aux);
		for (int r = 1; r <= _reqServers; r++) {
			_varList[c - 1].push_back(Node(varNum, true, r, c, txtFile._VMList[c - 1]._jobid));
			varNum++;
		}
	}

	for (int s = 0; s < _reqServers; s++) {
		for (int c = 1; c <= _nVM; c++) {
			for (int r = 1; r <= _sortedServerList[(int)_serverList.size()-s-1]._score; r++) {
				_varList[c - 1].push_back(Node(varNum, true, r, c, txtFile._VMList[c - 1]._jobid));
				varNum++;
			}
		}
	}

}

vector<Server> List::sortServerbyscore() {
	list<int> aux;
	vector<Server> aux2=_serverList;
	int j=0, i=0;

	for (int i = 0; i < (int) _serverList.size(); i++)
		aux.push_back(_serverList[i]._score);

	aux.sort();
	vector<int> v{ aux.begin(), aux.end() };

	vector<Server> sorted;

	while(sorted.size() != aux2.size()){

				if (aux2[j]._score == v[i] && aux2[j]._sorted == false)
				{
					sorted.push_back(aux2[j]);
					aux2[j]._sorted = true;
					j = 0;
					i++;
				}else{
				j++;
				}
	}
	return sorted;
}
