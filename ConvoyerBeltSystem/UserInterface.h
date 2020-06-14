#pragma once
#include "KeyPad.h"
#include "Potentiometer.h"
#include "ICommunication.h"

class UserInterface: public ICommunication
{
private: 
	KeyPad* keyPad;
	Potentiometer* potentiometer;

public: 

	bool updateCommunicationType = false;

	UserInterface();
	virtual ~UserInterface();
	Command* parse();
};

