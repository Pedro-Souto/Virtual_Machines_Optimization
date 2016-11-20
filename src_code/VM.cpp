#include "Classes.h"


VM::VM() {}

VM::VM(int jobid, int VMindex, int CPU, int RAM, bool Collo) {
	
	_jobid = jobid;
	_VMindex = VMindex;
	_CPU = CPU;
	_RAM = RAM;
	_Collo = Collo;

}

int VM::getScore() {
	if (_CPU > _RAM)
		return _CPU;
	else
		return _RAM;
}
