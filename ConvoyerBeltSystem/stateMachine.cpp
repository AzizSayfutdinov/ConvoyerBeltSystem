
#include <queue>
#include <semaphore.h>
#include <errno.h>
#include "defines.h"
#include "diaTimer.h"
#include "stateTable.h"
#include "stateMachine.h"
#include "IdleState.h"

StateMachine :: StateMachine() {
	// Create the instance
	currentState = new IdleState(this);		// default start state
	return;
}

StateMachine :: ~StateMachine() {
	int diagramNo;
	for (diagramNo = 0; diagramNo < diagrams; diagramNo++) {
		delete diaTimerTable[diagramNo]; // Delete the existing timer objects
		}
	return;
}

void StateMachine :: init() {
	// Create the semaphores needed
	if (sem_init(&semQueue, 0, 1) != 0)		// Damit man sicher ist, dass amn der einzige ist, der die Qeueu verwendet
		perror("Sem init");
	if (sem_init(&semEvent, 0, 0) != 0)		// Für die Event Queue
		perror("Sem init");
	int diagramNo;
	for (diagramNo = 0; diagramNo < diagrams; diagramNo++) {	// timer muss kennen, von wem es erstellt wurde (durch this erreicht
		diaTimerTable[diagramNo] = new DiaTimer(this); // Create one timer object for each diagram
		diaTimerTable[diagramNo]->init(); // Initialize timer
		diaTimerTable[diagramNo]->timerName = timerNames[diagramNo]; // Assign numbers to timer objects
	}
	return;
}

void StateMachine :: sendEvent(std::string myEvent) {
	putEvent (myEvent); // Set the event in the queue of this object
	if(sem_post(&semEvent) != 0)
		perror("Sem post"); // Signal the arrival of the event through counting semaphore
	return;
}

void StateMachine :: putEvent(std::string myEvent) {		// in die qeueue einfügen
	if (sem_wait(&semQueue) != 0)
		perror ("Sem wait");
	queue.push(myEvent);
	if (sem_post(&semQueue) != 0)
		perror ("Sem post");
	return;
}

std::string StateMachine :: getEvent() {
	std::string myString;
	if (sem_wait(&semQueue) != 0)
		perror ("Sem wait");
	if (queue.empty() == false) {
		myString = queue.front();
		queue.pop();
	}
	if (sem_post(&semQueue) != 0)
		perror ("Sem post");
	return myString;
}

void StateMachine :: runToCompletion() {
	std::string actualEvent;
	int d,i,j;
	while (true) {
		if (sem_wait(&semEvent) != 0)
			perror ("Sem wait"); // Wait for an event to arrive
		actualEvent = getEvent(); // Get the event from the queue
//		printf(actualEvent.c_str()); // For debug purposes only
		for (d = 0; d < diagrams; d++) {
			for (i = 0; i < lines[d]; i++) {
				if ((actualState[d] == tab[d][i]->actState) && 
						(actualEvent == tab[d][i]->myEvent) && 
						((this->currentState->*tab[d][i]->condition)() == true)) { // Call the condition function which returns bool
					actualState[d] = tab[d][i]->nextState;


					// (*tab[d][i]->action)(); //Call the funtion defined by pointer action
					(this->currentState->*tab[d][i]->execute)();


					for (j = 0; j < lines[d]; j++) {
						if ((actualState[d] == tab[d][j]->actState) && 
								(tab[d][j]->myEvent == (diaTimerTable[d]->timerName))) {
							diaTimerTable[d]->startTimer(tab[d][j]->eventTime); // Look for timers to start next
							break;
						}
					}
					break;
				}
			}
		}
	}
}
