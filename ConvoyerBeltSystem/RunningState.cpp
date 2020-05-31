#include "RunningState.h"
#include "IdleState.h"

RunningState::RunningState(StateMachine* sm)
{
	this->sm = sm;
}

void RunningState::execute()
{
	cout << "running RunningState... " << endl;
}

bool RunningState::condition()
{
	return true;
}

void RunningState::update()
{
	sm->currentState = new IdleState(sm);
}
