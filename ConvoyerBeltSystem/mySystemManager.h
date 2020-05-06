#pragma once
#include "LocalMode.h"
#include "ChainMode.h"
#include "SpeedProfile.h"


class mySystemManager
{
private: 
	LocalMode* lm;
	ChainMode* cm;
	SpeedProfile* sp;

public: 
	mySystemManager();
	~mySystemManager();
	void init();
	void startStateMachine();

};

