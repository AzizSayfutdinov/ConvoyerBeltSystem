#include "ConveyorBelt.h"

ConveyorBelt::ConveyorBelt()
{
	display = new Display();
	init();
}

ConveyorBelt::~ConveyorBelt()
{
	delete this;
}

void ConveyorBelt::stopDisplayUI()
{
	this->stop == true;
}

void ConveyorBelt::init()
{
	currentMode = LocalMode::getInstance();
	this->workerDisplayUI = thread(&ConveyorBelt::displayUI, this); //start thread Display UI
}

void ConveyorBelt::showDisplayOutput()
{
	display->displayClear();

	// commands
	for (int i = 0; i < 7; i++) {
		display->displayLine(commands[i]);
	}
	for (int i = 0; i < 4; i++) {
		display->displayLine(commands2[i]);
	}

	usleep(10000);
	string s = typeid(*myConveyorBelt->currentMode).name();
	char* writable = new char[s.size() + 1];
	std::copy(s.begin(), s.end(), writable);
	writable[s.size()] = '\0'; // don't forget the terminating 0
	char* data = writable + 1;

	char* currentOpMode[2] = {
		stringToCharArray(new string("SYSTEM PARAMETERS: ")),
		stringToCharArray(new string("current operation mode: " + string(data)))
	};

	for (int i = 0; i < 2; i++) {
		display->displayLine(currentOpMode[i]);
	}

	char* currentState[4] = {
		"",
		"current states in statemaschine: ",
		"[LOCAL diagram]\t\t\t[CHAIN diagram]",
		stringToCharArray(new string(myStateMaschine->actualState[0] + "\t\t\t\t" + myStateMaschine->actualState[1]))
	};
	for (int i = 0; i < 4; i++) {
		display->displayLine(currentState[i]);
	}

	string dir;
	if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == 0) {
		dir = "Right";
	}
	else
	{
		dir = "Left";
	}

	string state;
	switch (myConveyorBelt->currentMode->motorController->getMotorState())
	{
	case MotorState::movingLeft: 
		state = "MovingLeft";
		break;
	case MotorState::movingRight: 
		state = "MovingRight";
		break;
	case MotorState::Stop: 
		state = "Stop";
		break;
	default:
		break;
	}

	char* motorInfo[9] = {
		"",
		"MOTOR PARAMETERS: ",
		stringToCharArray(new string("defined max speed: \t\t" + to_string(myConveyorBelt->currentMode->motorController->getConfiguredSpeedRPM()) + "rpm")),
		stringToCharArray(new string("direction of local mode: \t" + dir)),
		stringToCharArray(new string("motor state: \t\t\t" + state)), 
		"",
		"Note: - After starting program, select Local or Chain Mode first. ",
		"================================================================================",
		"CURRENT ACTIONS",
	};
	for (int i = 0; i < 9; i++) {
		display->displayLine(motorInfo[i]);
	}

	// print current action
	display->displayLine(stringToCharArray(currentAction));

}

int ConveyorBelt::displayUI()
{
	while (!stop)
	{
		// test
		// displayMutex.lock();
		showDisplayOutput();
		usleep(500000);
		// this_thread::sleep_for(chrono::milliseconds(300));		

	}
	return 0;
}


