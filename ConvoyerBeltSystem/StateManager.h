#pragma once
#include "ChainMode.h"
#include "LocalMode.h"
#include "SpeedProfile.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "stateTable.h"
#include "myFunctions.h"
#include <string.h>
#include "Helpers.h"

class StateManager
{
private: 
	int n, m;	// to determine dynamically if possible
	StateMachine* myStateMaschine;
	Keyboard* myKeyboard;

	LocalMode* local;

public: 
	StateManager();
	~StateManager();
	void init();
	void startStateMaschine();

	// for testing
	void readKeyInputs();

};



