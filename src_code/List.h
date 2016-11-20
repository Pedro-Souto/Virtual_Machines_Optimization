#pragma once

#include <list>
#include <algorithm>
#include "importTXT.h"
#include "Classes.h"


 using namespace std;
class List {

public:
	vector<VM> _VMList;
	vector<int> _jobList;
	vector<Server> _serverList;
	vector<Server> _sortedServerList;
	vector<vector <Node> > _varList;
	volatile int _nJobs = (int) _jobList.size();
	volatile int _nVM = (int) _VMList.size();
	volatile int _nServers = (int) _serverList.size();
	volatile int _reqServers;

	List();
	List(vector<VM> VMlist, vector<Server> serverlist);

	int sumRAMVMs();
	int sumCPUVMs();
	int calc_maxVMIndex();
	vector<int> getjobList();
	vector<VM> sortVMbyjob();
	int getNJobsbyid(int jobid);
	void setVarList(importTXT txtFile);
	void setReqServers(int reqServers);
	vector<Server> sortServerbyscore();
};
