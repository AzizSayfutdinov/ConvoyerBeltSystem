#pragma once
#include "Mode.h"
#include "Command.h"
#include "string"
#include "Network.h"

using namespace std; 

class ChainMode : public Mode
{
private: 

	static ChainMode* instance;
	ChainMode();

public: 
	static ChainMode* getInstance();
	Network* network;
	Command* recv();
	void send(Command* command);
};

