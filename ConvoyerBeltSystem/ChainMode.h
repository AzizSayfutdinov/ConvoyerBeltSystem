#pragma once
#include "Mode.h"
#include "Command.h"
#include "string"
#include "StateChart.h"

using namespace std; 

class ChainMode : public Mode, public StateChart
{
private: 

public: 
	ChainMode();
	int send(Command command);
	int handleRequest(string ReadyWait);	// TODO: choose proper datatype for ready and wait status. maybe even a class for better usability
	int recv();
};

