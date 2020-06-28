#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <thread>
#include "stateMachine.h"
#include "Command.h"

#define TCP_PORT 5555
#define BUF_SIZE 128

using namespace std;

class TCPClient
{
private: 
	int sock;
	sockaddr_in serverAddr;
	char* test = "Hello from Client";
	in_addr_t IPAddress;
	int port;
	void connectToServer();
	void threadServerHandler();
	void handleServerInput();

public: 

	// bool updateCommunicationType = false;
	char buffer[BUF_SIZE];
	Command* currentCommand;	// no really needed. Potential extenstion of functionality
	Command* getCurrentCommand();

	TCPClient(in_addr_t serverAddress, int port);
	TCPClient(char* IPAddress, int port);
	TCPClient();
	int init();
	void sendData(string data);


};

