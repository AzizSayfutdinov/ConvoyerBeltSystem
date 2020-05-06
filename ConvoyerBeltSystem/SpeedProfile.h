#pragma once
#include "StateChart.h"
#include "MotorController.h"

class SpeedProfile: public StateChart
{
public: 
	SpeedProfile();
	
	// testFunctions for SM Test
	void startTimer();


};

