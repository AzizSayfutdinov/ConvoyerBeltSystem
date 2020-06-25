#pragma once
#include "ICommunication.h"
#include "TCPClient.h"
#include "TCPServer.h"
#include "SystemLocation.h"

class Network: public ICommunication
{
private: 
	Network();
	static Network* instance;

public: 

	TCPServer* server;
	TCPClient* rightConveyorBelt;
	static Network* getInstance();
	
	Command* parse();
	void send(Command* cmd);
	void send(string data, SystemLocation src, SystemLocation dest);
	void send(string data, SystemLocation dest);
};

