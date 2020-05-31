#pragma once
#include "State.h"
#include "StartState.h"
#include "stateMachine.h"

class IdleState: public State
{
public:
	StateMachine* sm;

	IdleState(StateMachine* sm);
	void execute();
	bool condition();
	void update();
};

