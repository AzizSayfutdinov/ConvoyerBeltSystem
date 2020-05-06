#include "TestEvents.h"

bool evFollowProfile() {
	// (1) recv(commend = followProfile)
	Keyboard* k = new Keyboard();
	char evChar = '1';
	if (k->getPressedKey() == evChar) {
		return true;
	}
	return false;
}

bool evStopFollowProfile()
{
	Keyboard* k = new Keyboard();
	char evChar = '2';

	if (k->getPressedKey() == evChar) {
		printf("Event: Stop Follow Profile");
		return true;
	}
	return false;
}

bool evFinishedProfile()
{
	printf("Event: Finished Profile");
	return false;
}

// waitTime in ms
bool evTimerHandler(int waitTime) {
	this_thread::sleep_for(chrono::milliseconds(waitTime));		// wait 
	printf("Event: Timer finished");
	return true;
}

bool evMotorControllerTotalSteps() {
	MotorController* mc = new MotorController();
	if (mc->totalSteps <= 400) {
		return false;
	}
	printf("Event: Total steps reached");
	return true;
}