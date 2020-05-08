#include "StateManager.h"


using namespace std;

StateManager::StateManager()
{
	n = 0;
	m = 0;
	myStateMachine = new StateMachine();
	myKeyboard = new Keyboard();

	local = new LocalMode();
	chain = new ChainMode();
	profile = new SpeedProfile();
}

StateManager::~StateManager()
{
	delete this;
	return;
}

void StateManager::init()
{
	// add state charts
	// myStateMachine->tab[0][0] = new TableEntry((__cxx11::string)"Idle", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdLocal", 0, (local->*(&LocalMode::noAction))(), (local->*(&LocalMode::noCondition))()  );
	
	// myStateMachine->tab[0][1] = new TableEntry((__cxx11::string)"Local", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdSpeed", 0, /*lm.getMotorController.setSpeed, */, lm->noCondition);
}

void StateManager::startStateMaschine()
{
	myStateMachine->runToCompletion();
	return;
}
