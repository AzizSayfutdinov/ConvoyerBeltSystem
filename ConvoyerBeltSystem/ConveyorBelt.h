#pragma once

#include "LocalMode.h"
#include "ChainMode.h"
#include "stateMachine.h"
#include <mutex>

class ConveyorBelt
{
public: 
	ConveyorBelt();
	~ConveyorBelt();
	Mode* currentMode;
	mutex updateMutex;

private:
	/*
	Purpose updateCurrentCommunicationType: 
	Das setzen des CurrentCommunicationType im TCPServer geht nicht, weil durch das includieren des ConveyorBelt.h es zu einer zirkul�ren Referenz kommt. 
	Daher muss das anders gel�st werden: update Funktion im Thread, welches schaut, ob ein update gemacht werden muss. 
	Suche im: 
		- TCP Server
		- TCP Client 
		- Telnet Server
		- UserInterface
	*/
	void updateCurrentCommunicationType();

	/*
	Instantiate all needed classes
	Both local and chain mode have to be instiate at the very be, so that the threads(tcp connections, user input from keypad)
	can start at the very beginning
	Singleton for communication classes maybe not needed. No new instantiation during runtime, only reassignments.
	*/
	void init();	
};

extern ConveyorBelt* myConveyorBelt;

