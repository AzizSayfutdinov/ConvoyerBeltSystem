#pragma once

#include <thread>
#include "defines.h"
#include <iostream>
#include "Motor.h"
#include "SpeedProfile.h"

using namespace std;

class MotorController
{
public:

	Motor* myMotor;
	SpeedProfile* mySpeedProfile;

	int direction = 1;		// 1 = right & 0 = left
	MotorController(Motor* motor, SpeedProfile* profile); //call init() and starts thread, which polls variable 'profileRunning' --> startProfile() sets the variable to true
	//move for time 1s !!! implementieren!
	int move(Direction Direction);
	int stop(); //resets the step counter! Neccessary to memorize step counter?!
	int setSpeedInRPM(int speed); 
	int getConfiguredSpeedRPM();
	double getCurrentSpeedRPM();
	int setMotorDutyCycle(int duty);
	int enableMotorPWM();

	// speed set by user
	Direction getConfiguredDirection(); 
	int setDirection(Direction direction);
	MotorState getMotorState();
	int setMotorState(MotorState state);

	//enum MotorState
	//{
	//	movingLeft, movingRight, Stop
	//};
	MotorController();
	
	int setDirection(int direction);
	int move(bool Direction); //time neccessary?


	int getStepCounter();
	int resetStepCounter();
	int incrementStepCounter();
	int startProfile();
	//int updateController();
	void oneStep();
	int followProfile();
	bool readyToRecvPayload();
	bool finishedProfile();

private:
	
	bool profileRunning = false;
	int currentSteps;
	double currentSpeed = 1000;		// default: 1000 rpm
	char currentState[MAX_STATE_NAME];
	thread threadFollowProfile;

};

