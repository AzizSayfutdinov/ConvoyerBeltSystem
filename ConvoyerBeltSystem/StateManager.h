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
	void init();
	StateManager();
	~StateManager();
	void startStateMaschine();

};

// action and condition functions
void selectLocalMode();
void selectChainMode();
void connectToRight();
void setSpeedPotentiometer();
void setSpeedTelnet();
void setDirectionKeyPad();
void setDirectionTelnet();
void followProfile();
void followProfileChain();
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
void releasePayload();

bool noCondition();
bool falseCondition();
bool isProfileFinished();
bool readyToReceive();
