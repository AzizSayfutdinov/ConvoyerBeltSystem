#pragma once
#include "ChainMode.h"
#include "LocalMode.h"
#include "SpeedProfile.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "stateTable.h"
#include "myFunctions.h"

class StateManager
{
private: 
	int n, m;	// determined dynamically
	StateMachine* myStateMachine;
	Keyboard* myKeyboard;

	LocalMode* local;
	ChainMode* chain;
	SpeedProfile* profile;

public: 
	StateManager();
	~StateManager();
	void init();
	void startStateMaschine();

};

