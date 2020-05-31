
#ifndef STATETABLE_H_
#define STATETABLE_H_

#include <string>
#include "State.h"

class TableEntry {
public:
	TableEntry(	
	std::string _actState,
	std::string _nextState,
	std::string _myEvent,
	int _eventTime,
	void (State::*execute)(),
	bool (State::*condition)()
	//void (*_action)(),	// change to (StateChart::*fpAction)()
	//bool (*_condition)()
	);
	std::string actState;
	std::string nextState;
	std::string myEvent;
	int eventTime;
	void (State::*execute)();
	bool (State::*condition)();
};

#endif // STATETABLE_H_
