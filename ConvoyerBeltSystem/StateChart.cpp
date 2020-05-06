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
	return;
}

bool StateChart::noCondition()
{
	return true;
}
