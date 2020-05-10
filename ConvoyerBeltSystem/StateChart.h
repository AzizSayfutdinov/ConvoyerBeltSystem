#pragma once
#include <vector>
#include "stateTable.h"
#include <iostream>

using namespace std;

class StateChart
{
public:
	StateChart();
	vector<TableEntry*>* tableEntries;
	void addTableEntry(TableEntry* tableEntry);
	void removeLastTableEntry();

	// used for tests
	void noAction();
	bool noCondition();
};

// General types pointing to actions and conditions 
typedef void (StateChart::* fpAction)();
typedef bool (StateChart::* fpCondition)();