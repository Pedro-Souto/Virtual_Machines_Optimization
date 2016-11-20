#include "Classes.h"

Node::Node() {}

Node::Node(int id, bool state, int server, int VM, int job) {
	_id = id;
	_state = state;
	_server = server;
	_VM = VM;
	_job = job;
}