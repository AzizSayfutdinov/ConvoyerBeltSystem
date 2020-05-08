#pragma once
#include "Command.h"
#include "MotorController.h"
#include "Display.h"

class Mode
{
private: 
	Display d;
	Command i;

public: 
	virtual int recv() = 0;

protected: 
	MotorController* controller = new MotorController();
	Command* currentCommand;


};

