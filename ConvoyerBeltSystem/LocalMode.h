#pragma once
#include "Mode.h"
#include "StateChart.h"

class LocalMode: public Mode, public StateChart
{
private: 

public: 
	LocalMode();
	int recv();
	void testAction();
	void idleAction();
	void startAction();
	void runningAction();

};

