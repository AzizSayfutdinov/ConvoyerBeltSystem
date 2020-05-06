
#include "stateTable.h"
#include "systemManager.h"
#include "stateMachine.h"
#include "keyboard.h"
#include "myFunctions.h"

int n, m;
StateMachine * myStateMachine;
Keyboard* myKeyboard;

SystemManager :: SystemManager() {
	// Create the instance
	return;
}

void SystemManager ::init() {

	// Create instance of state machine
	myStateMachine = new StateMachine;

	// Initialize table for all diagrams, event time in ms
	// The maximum size of the table is defined in defines.h:
	// MAXDIA = 9, MAXLINES = 66
	// Should these be exceeded, please correct!

	myStateMachine->tab[0][0] = new TableEntry ("StateA","StateA","Timer0",2000,myAction00,myCondition00);
	myStateMachine->tab[0][1] = new TableEntry ("StateA","StateB","Timer0",2000,myAction01,myCondition01);
	myStateMachine->tab[0][2] = new TableEntry ("StateB","StateA","Trigg0",0,myAction02,myConditionTrue);

	myStateMachine->tab[1][0] = new TableEntry ("StateC","StateD","Trigg1",0,myAction10,myConditionTrue);
	myStateMachine->tab[1][1] = new TableEntry ("StateD","StateD","Timer1",4000,myAction11,myCondition11);
	myStateMachine->tab[1][2] = new TableEntry ("StateD","StateE","Timer1",4000,myAction12,myCondition12);
	myStateMachine->tab[1][3] = new TableEntry ("StateE","StateC","Timer1",3000,myAction13,myConditionTrue);

	myStateMachine->tab[2][0] = new TableEntry ("StateK","StateK","Timer2",500,myAction20,myConditionTrue);

	// Initialize timer names for all diagrams
	// Timer names shall have the name Timer followed by the diagram number
	myStateMachine->timerNames[0] = "Timer0";
	myStateMachine->timerNames[1] = "Timer1";
	myStateMachine->timerNames[2] = "Timer2";

	// Initialize line numbers for all diagrams
	myStateMachine->lines[0] = 3;
	myStateMachine->lines[1] = 4;
	myStateMachine->lines[2] = 1;

	// Initialize first state for all diagrams
	myStateMachine->actualState[0] = "StateA";
	myStateMachine->actualState[1] = "StateC";
	myStateMachine->actualState[2] = "StateK";
	
	// Set the actual number of diagrams
	myStateMachine->diagrams = 3;

	// Initialize state machine
	myStateMachine->init();
	
	// Start timer for each diagram which needs one in the first state!
	// In my case these are diagram 0 and 2
	myStateMachine->diaTimerTable[0]->startTimer(myStateMachine->tab[0][0]->eventTime);
	myStateMachine->diaTimerTable[2]->startTimer(myStateMachine->tab[2][0]->eventTime);

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;

	// Create instance of my Keyboard
	myKeyboard = new Keyboard;

	return;
}

SystemManager :: ~SystemManager() {
	return;
}

void SystemManager :: startStateMachine() {
	// Start the state machine. This method blocks, so no while(1) is needed.
	myStateMachine->runToCompletion();
	return;
}

void myAction00() {
	printf(" StateA -> Transition00 -> StateA\n"); 
	n++;
	return;
}

void myAction01() {
	printf(" StateA -> Transition01 -> StateB\n"); 
	myStateMachine->sendEvent("Trigg1");	// hier muss bei klick des KB diese Methode ausgeführt werden
	return;									// Das heißt, dass Trigger über string gelöst werden
}

void myAction02() {
	printf(" StateB -> Transition02 -> StateA\n"); 
	n = 0;
	return;
}

void myAction10() {
	printf(" StateC -> Transition10 -> StateD\n"); 
	m = 0;
	return;
}

void myAction11() {
	printf(" StateD -> Transition11 -> StateD\n"); 
	m++;
	return;
}

void myAction12() {
	printf(" StateD -> Transition12 -> StateE\n"); 
	return;
}

void myAction13() {
	printf(" StateE -> Transition13 -> StateC\n"); 
	myStateMachine->sendEvent("Trigg0");
	return;
}

void myAction20() {
	myKeyboard->getPressedKey();	// "Do nothing" - action
	return;
}

bool myConditionTrue() {
	return true;
}

bool myCondition00() {
	if (n < 5) {
		return true;
	}
	else return false;
}

bool myCondition01() {
	if (n >= 5) return true;
	else return false;
}

bool myCondition11() {
	if (m < 4) return true;
	else return false;
}

bool myCondition12() {
	if (m >= 4) return true;
	else return false;
}
