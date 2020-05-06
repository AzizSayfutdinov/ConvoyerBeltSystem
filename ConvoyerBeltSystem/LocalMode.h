#pragma once
#include "Mode.h"
#include "StateChart.h"

class LocalMode: public StateChart, public Mode
{
private: 
	int i = 0;

public: 
	LocalMode();
	int recv();
};

