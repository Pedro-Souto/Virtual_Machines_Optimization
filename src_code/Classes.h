#pragma once

#include <iostream>
#include <string>
#include <string.h>


using namespace std;
class Node {
public:
	int _id;
	bool _state;
	int _server;
	int _VM;
	int _job;


	Node();
	Node(int id, bool state, int server, int VM, int job);

};

class Server {
public:
	int _id;
	int _CPU;
	int _RAM;
	int _score;
	bool _sorted = false;

	Server();
	Server(int id, int CPU, int RAM);
	
	int score();

};


class VM {
public:
	int _jobid;
	int _VMindex;
	int _CPU;
	int _RAM;
	bool _Collo;

	VM();
	VM(int jobid,	int VMindex, int CPU, int RAM, bool Collo);
	inline int getScore();


};