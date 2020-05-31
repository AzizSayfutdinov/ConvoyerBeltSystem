#pragma once
#include "State.h"
#include <iostream>
#include "stateMachine.h"

using namespace std;

class RunningState : public State
{

public: 
	StateMachine* sm;

	RunningState(StateMachine* sm);
	void execute();
	bool condition();
	void update();

};

