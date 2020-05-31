#include "StartState.h"

StartState::StartState(StateMachine* sm)
{
	this->sm = sm;
}

void StartState::execute()
{
	cout << "running StartState ... " << endl;
}

bool StartState::condition()
{
	return true;
}

void StartState::update()
{
	sm->currentState = new RunningState(sm);
}
