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
	void noAction();
	bool noCondition();
};