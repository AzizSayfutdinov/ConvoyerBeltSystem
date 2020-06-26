#pragma once
#include "Command.h"

class ICommunication
{
public: 
	virtual Command* parse() = 0;
	virtual void send(Command* cmd) = 0;
};