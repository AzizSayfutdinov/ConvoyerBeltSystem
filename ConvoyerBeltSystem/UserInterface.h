#pragma once
#include "KeyPad.h"
#include "Potentiometer.h"
#include "ICommunication.h"
#include "Helpers.h"

class UserInterface: public ICommunication
{
private: 
	KeyPad* keyPad;
	Potentiometer* potentiometer;
	static UserInterface* instance;
	UserInterface();

public: 

	static UserInterface* getInstance();

	~UserInterface();
	Command* parse();
	void send(Command* cmd);
};

