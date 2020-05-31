#pragma once
#include "State.h"
#include "RunningState.h"

class StartState: public State
{
public:
	StateMachine* sm;

	StartState(StateMachine* sm);
	void execute();
	bool condition();
	void update();
};

