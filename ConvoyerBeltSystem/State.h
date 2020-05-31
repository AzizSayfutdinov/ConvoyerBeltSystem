#pragma once
#include "StateChart.h"

class State: public StateChart
{
public: 
	virtual void execute() = 0;
	virtual void update() = 0;
	virtual bool condition() = 0;

};

// Define class member function pointers
typedef void (State::*fptrAction)();
typedef bool (State::*fptrCondition)();

// Notes: 

// - Each derived state has to know the statemaschine
// - Each derived state knows the next state