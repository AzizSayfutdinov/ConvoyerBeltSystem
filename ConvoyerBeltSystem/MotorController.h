#pragma once

#include <thread>
#include "defines.h"
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:
	MotorController(Motor* motor, SpeedProfile* profile); //call init() and starts thread, which polls variable 'profileRunning' --> startProfile() sets the variable to true
	int setSpeed(int speed); 
	int setDirection(Direction direction);
	int move(bool Direction); 
	int stop(); //resets the step counter! Neccessary to memorize step counter?!
	MotorState getMotorState();
	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int startProfile();
	double getCurrentSpeed();

	bool readyToRecvPayload();
	bool finishedProfile();
private:
	int followProfile();
	bool profileRunning;
	int currentSteps;
	double currentSpeed;
	char currentState[MAX_STATE_NAME];
	thread workProfile;
	Motor* myMotor;
	SpeedProfile* mySpeedProfile;
};

