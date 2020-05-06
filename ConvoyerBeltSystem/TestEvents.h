#pragma once
#include "keyboard.h"
#include "MotorController.h"
#include <thread>
#include <chrono>

using namespace std;

// testEvents for SM testing

bool evFollowProfile();
bool evStopFollowProfile();
bool evFinishedProfile();
bool evTimerHandler(int waitTime); // waitTime in ms
bool evMotorControllerTotalSteps();