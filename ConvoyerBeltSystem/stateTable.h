
#ifndef STATETABLE_H_
#define STATETABLE_H_

#include <string>

class TableEntry {
public:
	// ctor
	TableEntry(	
	std::string _actState,
	std::string _nextState,
	std::string _myEvent,
	int _eventTime,
	void (*_action)(),
	bool (*_condition)()
	);
	std::string actState;
	std::string nextState;
	std::string myEvent;
	int eventTime;
	void (*action)();
	bool (*condition)();
};

#endif // STATETABLE_H_
