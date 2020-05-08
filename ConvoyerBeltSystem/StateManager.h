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
	int n, m;	// to determine dynamically if possible
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

