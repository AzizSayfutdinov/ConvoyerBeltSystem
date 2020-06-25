#pragma once
#include <thread>

#include "TCPServer.h"
#include "ICommunication.h"


class TelnetServer: public ICommunication
{
private: 
	int telnetPort = 23;
	TCPServer* telnetServer;
	int speedBuffer = 0;

	TelnetServer();
	static TelnetServer* instance;

public: 

	// check if acually needed
	double buffer2 = 0;		// buffer to save last speed value
	bool dirBuffer = true;	// buffer to save last direction value: true = right & false = left
	// bool updateCommunicationType = false;
	static TelnetServer* getInstance();
	
	Command* parse();
	void send(Command* cmd);
	void sendData(string data);
	// void handleUserInput();

};

