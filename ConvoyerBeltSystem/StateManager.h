#pragma once
#include <iostream>
#include <thread>
#include <mutex>

#include "stateMachine.h"
#include "keyboard.h"

#include "Helpers.h"
#include "ConveyorBelt.h"

using namespace std;


class StateManager
{
private: 

public: 

	mutex mtx;
	void init();
	StateManager();
	~StateManager();
	void startStateMaschine();

};

// action and condition functions
void noAction();
void startLocalMode();
void startChainMode();
void selectLocalMode();
void selectChainMode();
void setModeTelnet();
void connectToRight();
void setSpeedPotentiometer();
void setSpeedTelnet();
void setDirectionKeyPad();
void setDirectionTelnet();
void followProfile();
void finishedProfile();
void stopMotor();
void updateMotorController();
void handleRequest();
void handleRequestRepeat();
void checkRequestBuffer();
void startSlowMovement();
void requesting();
void handleWait();
void handleReady();
void completingPassload();
void releasePayload();


bool noCondition();
bool falseCondition();
bool isProfileFinished();
bool readyToReceive();

// Function for reading keyInputs
void readKeyInputs();






// Functions for testing
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
