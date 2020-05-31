#include "IdleState.h"

IdleState::IdleState(StateMachine* sm)
{
	this->sm = sm;
}

void IdleState::execute()
{
	cout << "running IdleState ... " << endl;
}

bool IdleState::condition()
{
	return true;
}

void IdleState::update()
{
	sm->currentState = new StartState(sm);
}
