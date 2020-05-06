#include "mySystemManager.h"
#include "stateTable.h"
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"

int myN, myM;
StateMachine* stateMaschine;
Keyboard* keyBoard;

using namespace std;

mySystemManager::mySystemManager()
{
	//lm = new LocalMode();
	//cm = new ChainMode();
	sp = new SpeedProfile();
}

void mySystemManager::init()
{
	// Create instance of state machine
	stateMaschine = new StateMachine;

	// Initialize table for all diagrams, event time in ms
	// The maximum size of the table is defined in defines.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	// MY DIAGRAMS
	// -- Local
	// myStateMachine->tab[0][0] = new TableEntry((__cxx11::string)"Idle", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdLocal", 0, lm->noAction, lm->noConditiond);
	// myStateMachine->tab[0][1] = new TableEntry((__cxx11::string)"Local", (__cxx11::string)"Local", (__cxx11::string)"RecvCmdSpeed", 0, /*lm.getMotorController.setSpeed, */, lm->noCondition);

	// Initialize timer names for all diagrams
	// Timer names shall have the name Timer followed by the diagram number
	stateMaschine->timerNames[0] = "Timer0";
	stateMaschine->timerNames[1] = "Timer1";
	stateMaschine->timerNames[2] = "Timer2";

	// Initialize line numbers for all diagrams
	stateMaschine->lines[0] = 3;
	stateMaschine->lines[1] = 4;
	stateMaschine->lines[2] = 1;

	// Initialize first state for all diagrams
	stateMaschine->actualState[0] = "StateA";
	stateMaschine->actualState[1] = "StateC";
	stateMaschine->actualState[2] = "StateK";

	// Set the actual number of diagrams
	stateMaschine->diagrams = 3;

	// Initialize state machine
	stateMaschine->init();

	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	stateMaschine->diaTimerTable[0]->startTimer(stateMaschine->tab[0][0]->eventTime);
	stateMaschine->diaTimerTable[2]->startTimer(stateMaschine->tab[2][0]->eventTime);

	// Initial actions can be done here, if needed!
	myN = 0;
	myM = 0;

	// Create instance of my Keyboard
	keyBoard = new Keyboard;

	return;
}

void mySystemManager::startStateMachine()
{
	// Start the state machine. This method blocks, so no while(1) is needed.
	stateMaschine->runToCompletion();
	return;
}


