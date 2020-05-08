#include "StateChart.h"

StateChart::StateChart()
{

}

void StateChart::addTableEntry(TableEntry* tableEntry)
{
	tableEntries->push_back(tableEntry);
}

void StateChart::removeLastTableEntry()
{
	tableEntries->pop_back();
}

void StateChart::noAction()
{
	cout << "Called noAction of StateChart class ... " << endl;
}

bool StateChart::noCondition()
{
	return true;
}
