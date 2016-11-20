#include "Classes.h"


Server::Server() {}

Server::Server(int id, int CPU, int RAM) {
	_id = id;
	_CPU = CPU;
	_RAM = RAM;
	_score = score();
}

int Server::score() { 
	if (_RAM < _CPU)
		return _RAM;
	else
		return _CPU;
}
