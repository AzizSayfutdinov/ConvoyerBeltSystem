#pragma once
#include <thread>

#include "TCPServer.h"
#include "ICommunication.h"


class TelnetServer: public ICommunication
{
private: 
	int telnetPort = 23;
	TCPServer* telnetServer;
	TelnetServer();
	static TelnetServer* instance;

public: 
	static TelnetServer* getInstance();	
	Command* parse();
	void send(Command* cmd);
	void sendData(string data);

};

