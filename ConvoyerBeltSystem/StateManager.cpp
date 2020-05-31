#include "StateManager.h"


using namespace std;

StateManager::StateManager()
{
	n = 0;
	m = 0;
	myStateMaschine = new StateMachine();
	myKeyboard = new Keyboard();

	local = new LocalMode();

	init();
}

StateManager::~StateManager()
{
	delete this;
	return;
}

void StateManager::init()
{
	// add states for List<State> listOfStates: each state has its own TableEntry
	fptrAction action = &State::execute;
	fptrCondition condition = &State::condition;

	myStateMaschine->tab[0][0] = new TableEntry("Idle", "Start", "CmdToStart", 0, action, condition);
	myStateMaschine->tab[0][1] = new TableEntry("Start", "Running", "CmdToRunning", 0, action, condition);
	myStateMaschine->tab[0][2] = new TableEntry("Running", "Idle", "CmdToIdle", 0, action, condition);


	// myStateMachine->tab[0][0] = new TableEntry((__cxx11::string)"Idle", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdLocal", 0, (local->*(&LocalMode::noAction))(), (local->*(&LocalMode::noCondition))()  );
	
	// myStateMachine->tab[0][1] = new TableEntry((__cxx11::string)"Local", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdSpeed", 0, /*lm.getMotorController.setSpeed, */, lm->noCondition);
}

void StateManager::startStateMaschine()
{
	myStateMaschine->runToCompletion();
	return;
}

void StateManager::readKeyInputs()
{
	
		char readKey;

		while (true) {

			readKey = myKeyboard->getPressedKey();
			sleep(0.1);

			// Evaluate
			// -- Events		
			// [1] CmdToStart
			// [2] CmdToRunning
			// [3] CmdToIdle


			// mtxKeys.lock();
			switch (readKey)
			{
			case '0':
				myStateMaschine->sendEvent("motorControllerFinishedProfile");
				break;
			case '1':
				myStateMaschine->sendEvent("CmdToStart");
				break;
			case '2':
				myStateMaschine->sendEvent("CmdToRunning");
				break;
			case '3':
				myStateMaschine->sendEvent("CmdToIdle");
				break;
			case '4':
				myStateMaschine->sendEvent("RecvCmdFollowProfile");
				break;
			case '5':
				myStateMaschine->sendEvent("motorControllerFinishedProfile");
				break;
			case '6':
				myStateMaschine->sendEvent("RecvCmdChain");
				break;
			case '7':
				myStateMaschine->sendEvent("RecvCmdRequest");
				break;
			case '8':
				myStateMaschine->sendEvent("motorControllerReadToRecvPayload");
				break;
			case '9':
				myStateMaschine->sendEvent("SendRelease");
				break;
			case 'A':
				myStateMaschine->sendEvent("RecvCmdWait");
				break;
			case 'B':
				myStateMaschine->sendEvent("RecvCmdReady");
				break;
			case 'C':
				myStateMaschine->sendEvent("RecvCmdReleased");
				break;

			default:
				break;
			}
			// mtxKeys.unlock();
		

	}
}

