#pragma once
#include "Mode.h"
#include "string"
#include "StateChart.h"

using namespace std; 

class ChainMode : public StateChart
{
private: 
	int i = 0;

public: 
	ChainMode();
	int send(Command command);
	int handleRequest(string ReadyWait);	// TODO: choose proper datatype for ready and wait status. maybe even a class for better usability
	int recv();
};

