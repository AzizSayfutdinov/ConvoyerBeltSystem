#include "StateManager.h"

// I need these global variables so that I can access them in my global action functions
// Tip: use prefix "my" for testing with global variables

mutex mtxKeys;
int n, m;		
StateMachine* myStateMaschine;
ConveyorBelt* myConveyorBelt;

StateManager::StateManager()
{
	myConveyorBelt = new ConveyorBelt();
}

StateManager::~StateManager()
{
	delete this;
}

void StateManager::init()
{
	myStateMaschine = new StateMachine();

	// gpio

	// DEFINE STATE CHARTS
	// Local Mode Chart
	myStateMaschine->tab[0][0] = new TableEntry("IdleLocal", "Local", "RecvCmdLocal", 0, selectLocalMode, noCondition);	// reset to local mit cmd
	myStateMaschine->tab[0][1] = new TableEntry("Local", "IdleLocal", "RecvCmdChain", 0, selectChainMode, noCondition);	// reset to local mit cmd
	myStateMaschine->tab[0][2] = new TableEntry("Local", "Local", "RecvCmdSetSpeedPoti", 0, setSpeedPotentiometer, noCondition);
	myStateMaschine->tab[0][3] = new TableEntry("Local", "Local", "RecvCmdSetSpeedTelnet", 0, setSpeedTelnet, noCondition);
	myStateMaschine->tab[0][4] = new TableEntry("Local", "Local", "RecvCmdDirectionKeyPad", 0, setDirectionKeyPad, noCondition);
	myStateMaschine->tab[0][5] = new TableEntry("Local", "Local", "RecvCmdDirectionTelnet", 0, setDirectionTelnet, noCondition);
	myStateMaschine->tab[0][6] = new TableEntry("Local", "FollowProfile", "RecvCmdFollowProfile", 0, followProfile, noCondition);
	myStateMaschine->tab[0][7] = new TableEntry("FollowProfile", "FollowProfile", "Timer0", 20, updateMotorController, isProfileFinished);
	myStateMaschine->tab[0][8] = new TableEntry("FollowProfile", "Local", "finishedProfile", 0, finishedProfile, noCondition);	
	myStateMaschine->tab[0][9] = new TableEntry("FollowProfile", "Local", "RecvCmdStopMotor", 0, stopMotor, noCondition);	

	// Chain Chart
	myStateMaschine->tab[1][0] = new TableEntry("IdleChain", "Chain", "RecvCmdChain", 0, selectChainMode, noCondition);
	myStateMaschine->tab[1][1] = new TableEntry("Chain", "IdleChain", "RecvCmdLocal", 0, selectLocalMode, noCondition);
	myStateMaschine->tab[1][2] = new TableEntry("Chain", "Chain", "ConnectToRight", 0, connectToRight, noCondition);
	myStateMaschine->tab[1][3] = new TableEntry("IdleChain", "IdleChain", "ConnectToRight", 0, connectToRight, noCondition);
	myStateMaschine->tab[1][4] = new TableEntry("Chain", "Requested", "RecvCmdRequest", 0, handleRequest, noCondition);
	myStateMaschine->tab[1][5] = new TableEntry("Requested", "Requested", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][6] = new TableEntry("Requested", "ReceivingPayload", "ReadyToRecvPayload", 0, startSlowMovement, readyToReceive);
	myStateMaschine->tab[1][7] = new TableEntry("ReceivingPayload", "ReceivingPayload", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][8] = new TableEntry("ReceivingPayload", "ReceivingPayloadFinished", "Timer1", 1000, releasePayload, noCondition);
	myStateMaschine->tab[1][9] = new TableEntry("ReceivingPayloadFinished", "ReceivingPayloadFinished", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][10] = new TableEntry("ReceivingPayloadFinished", "FollowProfile", "ReleasedPayload", 0, followProfileChain, noCondition);
	myStateMaschine->tab[1][11] = new TableEntry("FollowProfile", "FollowProfile", "Timer1", 20, updateMotorController, isProfileFinished);
	myStateMaschine->tab[1][12] = new TableEntry("FollowProfile", "Requesting", "finishedProfile", 0, requesting, isProfileFinished);
	myStateMaschine->tab[1][13] = new TableEntry("FollowProfile", "Chain", "RecvCmdStopMotor", 0, stopMotor, noCondition);
	myStateMaschine->tab[1][14] = new TableEntry("Requesting", "Requesting", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);
	myStateMaschine->tab[1][15] = new TableEntry("Requesting", "Requesting", "RecvCmdWait", 0, handleWait, noCondition);
	myStateMaschine->tab[1][16] = new TableEntry("Requesting", "Passload", "RecvCmdReady", 0, handleReady, noCondition);
	myStateMaschine->tab[1][17] = new TableEntry("Passload", "Chain", "RecvCmdRelease", 0, checkRequestBuffer, noCondition);
	myStateMaschine->tab[1][18] = new TableEntry("Passload", "Passload", "RecvCmdRequest", 0, handleRequestRepeat, noCondition);


	// Initialize timer names for all diagrams
	// e.g. Diagram 0 uses Timer0, ... 
	myStateMaschine->timerNames[0] = "Timer0";
	myStateMaschine->timerNames[1] = "Timer1";

	// Initialize line numbers for all diagrams
	myStateMaschine->lines[0] = 10;	
	myStateMaschine->lines[1] = 19;

	// Initialize first state for all diagrams
	myStateMaschine->actualState[0] = "IdleLocal";
	myStateMaschine->actualState[1] = "IdleChain";

	// Set the actual number of diagrams
	myStateMaschine->diagrams = 2;

	// Initialize state machine
	myStateMaschine->init();

	// Initial actions can be done here, if needed!
	n = 0;
	m = 0;
}

void StateManager::startStateMaschine()
{
	myStateMaschine->runToCompletion();
	this_thread::sleep_for(chrono::microseconds(50));
}

// Defining global functions
// ACTIONS
void selectLocalMode() {
	myConveyorBelt->currentMode = LocalMode::getInstance();
	myConveyorBelt->currentAction = new string("Selected Local Mode. ");
}

void selectChainMode() {
	myConveyorBelt->currentMode = ChainMode::getInstance();
	myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
	myConveyorBelt->currentAction = new string("Selected Chain Mode. ");
}

void setSpeedPotentiometer()
{
	myConveyorBelt->currentMode->communication = UserInterface::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	usleep(50000);		
	int speed = stoi(cmd->data);
	myConveyorBelt->currentMode->motorController->setSpeedInRPM(speed);
	myConveyorBelt->currentAction = new string("Set speed with potentiometer. ");
	
}

void setSpeedTelnet()
{
	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = TelnetServer::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	int speed = stoi(cmd->data);
	myConveyorBelt->currentMode->motorController->setSpeedInRPM(speed);
	myConveyorBelt->currentAction = new string("Set speed to " + to_string(speed) + " rpm with telnet. ");

}

void setDirectionKeyPad() {

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = UserInterface::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	string dir = cmd->data;

	if (dir == "left") {	// left
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Left);
		myConveyorBelt->currentAction = new string("Set direction to left with keyboard. ");
	}
	else if (dir == "right") {
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
		myConveyorBelt->currentAction = new string("Set direction to right with keyboard. ");
	}
	else
	{
		myConveyorBelt->currentAction = new string("Failed to set direction with keyboard. ");
	}

}

void setDirectionTelnet() {

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = TelnetServer::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	string dir = cmd->data;

	if (dir == "left\r\n") {	// left
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Left);
		myConveyorBelt->currentAction = new string("Set direction to left with telnet. ");
	}
	else if (dir == "right\r\n") {
		myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
		myConveyorBelt->currentAction = new string("Set direction to right with telnet. ");
	}
	else
	{
		myConveyorBelt->currentAction = new string("Direction not set. Cmd = " + dir);
	}
}

void connectToRight() {

	// read value from telnet cmd
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();
	
	string IP = cmd->data;
	((Network*)(myConveyorBelt->currentMode->communication))->rightConveyorBelt = new TCPClient(stringToCharArray(&IP), TCP_PORT);
	myConveyorBelt->currentAction = new string("Received IP-address of right conveyorbelt. ");
}

void followProfile() {
	if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == Right) {
		myConveyorBelt->currentMode->motorController->setMotorState(movingRight);

	}
	else if (myConveyorBelt->currentMode->motorController->getConfiguredDirection() == Left) {
		myConveyorBelt->currentMode->motorController->setMotorState(movingLeft);
	}
	Discrete_initialize();
	myConveyorBelt->currentAction = new string("Started following profile ... ");
}

void followProfileChain() {

	myConveyorBelt->currentMode->motorController->setDirection(Direction::Right);
	myConveyorBelt->currentMode->motorController->setMotorState(movingRight);

	Discrete_initialize();
	myConveyorBelt->currentAction = new string("Started following profile ... ");
}

void finishedProfile() {
	myConveyorBelt->currentMode->motorController->setMotorState(MotorState::Stop);
	myConveyorBelt->currentAction = new string("Finished profile. ");
}

void stopMotor() {
	myConveyorBelt->currentMode->motorController->stop();
}

void updateMotorController() 
{
	myConveyorBelt->currentMode->motorController->incrementStepCounter();
	myConveyorBelt->currentMode->motorController->followProfile();
	myConveyorBelt->currentAction = new string("Updating profile steps. ");
}

void handleRequest() 
{
	myConveyorBelt->currentMode->communication = Network::getInstance();

	Command* cmd = new Command("Ready", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Handling request from left conveyorbelt. ");
	myStateMaschine->sendEvent("ReadyToRecvPayload");
}

void releasePayload() {

	// send Event, check happens in condition
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("Release", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Received payload and released left conveyorbelt. ");
	myStateMaschine->sendEvent("ReleasedPayload");
}

void handleRequestRepeat() 
{
	// send back wait
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("Wait", Self, LeftConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);
	myConveyorBelt->currentAction = new string("Storing additional requests in request queue. ");
	
}

void checkRequestBuffer()
{
	myConveyorBelt->currentMode->motorController->stop();
	myConveyorBelt->currentMode->motorController->myMotor->setStatus(MotorState::Stop);

	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = myConveyorBelt->currentMode->recv();

	int reqBufferCount = stoi(cmd->data) - 1;	// first request is always processed

	myConveyorBelt->currentAction = new string("Checking Request buffer. Open requests: " + to_string(reqBufferCount));


	if (reqBufferCount > 0) {
		myStateMaschine->sendEvent("RecvCmdRequest");
	}
}

void startSlowMovement()
{
	myConveyorBelt->currentAction = new string("Starting slow movement for 1s. ");
	myConveyorBelt->currentMode->motorController->move(Direction::Right, 100);	// correct function?
}

void requesting()
{
	myConveyorBelt->currentAction = new string("Sent request to right conveyorbelt. Waiting for 'Wait' or 'Ready'. ");

	// send request to right
	myConveyorBelt->currentMode->communication = Network::getInstance();
	Command* cmd = new Command("Request", Self, RightConveyorBelt);
	myConveyorBelt->currentMode->send(cmd);

}

void handleWait()
{
	myConveyorBelt->currentAction = new string("Waiting for 'Ready' from right conveyorbelt. ");
	// stay in state
	// stop motor
	myConveyorBelt->currentMode->motorController->stop();
}

void handleReady()
{
	myConveyorBelt->currentAction = new string("Ready to pass load to right conveyorbelt. Waiting for 'Release'. ");
	myConveyorBelt->currentAction = new string("Ready to pass load to right conveyorbelt. Waiting for 'Release'. ");
	myConveyorBelt->currentMode->motorController->move(Direction::Right, 100);
}


// CONDITIONS
bool noCondition() {
	return true;
}

bool falseCondition()
{
	return false;
}

bool isProfileFinished() {
	int steps = myConveyorBelt->currentMode->motorController->getStepCounter();
	MotorState state = myConveyorBelt->currentMode->motorController->getMotorState();
	Direction direction = myConveyorBelt->currentMode->motorController->getConfiguredDirection();
	if (state == Stop)
	{
		myStateMaschine->sendEvent("finishedProfile");
		return false;
	}
	if (steps >= (RAMP_UP + RAMP_STEADY + RAMP_DOWN - 1)) {		
		myConveyorBelt->currentMode->motorController->stop();
		myConveyorBelt->currentMode->motorController->resetStepCounter();
		myStateMaschine->sendEvent("finishedProfile");
		return false;
	}
	if (steps < (RAMP_UP + RAMP_STEADY + RAMP_DOWN))
	{
		return true;
	}

}

bool readyToReceive()
{
	return myConveyorBelt->currentMode->motorController->readyToRecvPayload();

}
