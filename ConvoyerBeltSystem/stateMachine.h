
#ifndef STATEMACHINE_H_
#define STATEMACHINE_H_

#include "defines.h"
#include <string>
#include <queue>
#include <semaphore.h>
#include "diaTimer.h"
#include "stateTable.h"
#include "State.h"

class StateMachine {
public:
	StateMachine();
	~StateMachine();
	void init();
	void sendEvent(std::string myEvent);
	void runToCompletion();
	std::string actualState[MAXDIA];
	std::string timerNames[MAXDIA];
	int lines[MAXDIA];
	int diagrams;
	TableEntry* tab[MAXDIA][MAXLINES];
	std::string myEvent;
	DiaTimer * diaTimerTable[MAXDIA];

	// added
	State* currentState;


private:
	sem_t semQueue, semEvent;
	void putEvent(std::string myEvent);
	std::string getEvent();
	std::queue<std::string> queue;
};

#endif // STATEMACHINE_H_
