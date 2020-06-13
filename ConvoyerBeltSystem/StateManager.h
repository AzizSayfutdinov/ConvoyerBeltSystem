#pragma once
#include "keyboard.h"
#include "stateMachine.h"
#include <iostream>
#include "SpeedProfile.h"
#include <thread>
#include <mutex>
#include "MotorController.h"
#include "Motor.h"
#include "SpeedProfile.h"
#include "Encoder.h"
#include "Controller.h"
#include "Helpers.h"
#include "TelnetServer.h"
#include "TCPServer.h"
#include "TCPClient.h"
#include "ConveyorBelt.h"

using namespace std;


class StateManager
{
private: 
	Motor* motor;
	SpeedProfile* speedProfile;
	Encoder* encoder;
	Controller* controller;

public: 

	mutex mtx;

	StateManager();
	~StateManager();
	void init();
	void startStateMaschine();

};

// action and condition functions
void noAction();
void selectLocalMode();

// Function for reading keyInputs
void readKeyInputs();

// implement noAction() only once for actual implementation
void noAction1();
void noAction2();
void noAction3();
void noAction4();
void noAction5();
void actionSetSpeed1();
void actionSetSpeed2();
void actionSetDirection();
void actionFollowProfile1();
void actionFollowProfile2();
void actionSetSpeedAndSteps();
void actionHandleRequest_Wait1();
void actionHandleRequest_Wait2();
void actionHandleRequest_Wait3();
void actionHandleRequest_Wait4();
void actionHandleRequest_Ready();
void actionSendRequest();
void actionMotorStop1();
void actionMotorStop2();
void actionMotorMove();

bool noCondition();
bool conditionTotalSteps();
