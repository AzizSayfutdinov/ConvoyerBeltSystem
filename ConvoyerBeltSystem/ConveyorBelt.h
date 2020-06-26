#pragma once
#include "LocalMode.h"
#include "ChainMode.h"
#include "stateMachine.h"
#include <mutex>
#include <type_traits>
#include "Helpers.h"

using namespace std;

class ConveyorBelt
{
public: 
	ConveyorBelt();
	~ConveyorBelt();
	Mode* currentMode;
	mutex updateMutex;
	mutex displayMutex;
	Display* display;

	string* currentAction = new string("No Actions at the moment. ");
	void showDisplayOutput();
	int displayUI();
	void stopDisplayUI();
private:
	void init();
	bool stop = false;
	thread workerDisplayUI;

	char* commands[7] = {
		"KEYBOARD commands: ",
		"[1] right dir\t [2] left dir\t [3] start profile\t [4] stop profile",
		"[5] chain mode\t [6] local mode\t [7] speed with poti",
		"--------------------------------------------------------------------------",
		"TELNET commands: ",
		"[tel dir right]\t [tel dir left]\t\t [tel start]\t [tel stop]",
		"[tel mode chain] [tel mode local]\t [tel speed value]",
	};

	char* commands2[4] = {
		"--------------------------------------------------------------------------",
		"TCP commands: ",
		"[Request]\t [Wait]\t\t [Ready]\t [Release]",
		"==========================================================================",
	};

};

extern ConveyorBelt* myConveyorBelt;

