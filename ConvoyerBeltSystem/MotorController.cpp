#include "MotorController.h"

// extern MotorController* motorController;

MotorController::MotorController()
{
	myMotor = new Motor();
	mySpeedProfile = new SpeedProfile();
	//this->threadFollowProfile = thread(&MotorController::followProfile, this);
}

MotorController::MotorController(Motor* motor, SpeedProfile* profile) : myMotor(motor), mySpeedProfile(profile)
{
	this->myMotor->initMotor();
	this->threadFollowProfile = thread(&MotorController::followProfile, this);
}

int MotorController::setSpeedInRPM(int speed)
{

	return this->myMotor->setSpeedRPM(speed);
}

int MotorController::getConfiguredSpeedRPM()
{
	int a = this->myMotor->getSpeed();
	return a;
}

int MotorController::setDirection(int direction)
{
	return 0;
}


Direction MotorController::getConfiguredDirection()
{
	return myMotor->getDirection();
}

int MotorController::setDirection(Direction direction)
{
	return myMotor->setDirection(direction);
}

int MotorController::setMotorDutyCycle(int duty)
{
	int err = myMotor->setDutyCycle(duty);
	return err;
}

int MotorController::move(Direction direction)
{
	if (direction == Right) this->myMotor->setStatus(movingRight);
	else this->myMotor->setStatus(movingLeft);
	return this->myMotor->startMotor(direction);
}

int MotorController::move(Direction direction, int speed)
{
	if (direction == Right) this->myMotor->setStatus(movingRight);
	else this->myMotor->setStatus(movingLeft);
	return this->myMotor->startMotor(direction, speed);
}

int MotorController::enableMotorPWM()
{	
	int err = pwmSetEnable_B(this->myMotor->pwmMotor, 1);
	return err;
}

int MotorController::stop()
{	
	this->profileRunning = false;
	return this->myMotor->stopMotor();
}

int MotorController::getStepCounter()
{
	return this->mySpeedProfile->getStepCounter();
}

int MotorController::resetStepCounter()
{
	return this->mySpeedProfile->resetStepCounter();
}

int MotorController::incrementStepCounter()
{
	return this->mySpeedProfile->incrementStepCounter();
}


int MotorController::startProfile()
{
	this->enableMotorPWM();
}

int MotorController::followProfile()
{	
	unsigned int steps = mySpeedProfile->getStepCounter();
	int speed = this->getConfiguredSpeedRPM();		
	int desiredSpeed, currentSpeed, error;
	double output, duty, outputInvolts;
	pwmSetEnable_B(this->myMotor->pwmMotor, 1);
	//accelerate
	if (steps <= RAMP_UP) {
		desiredSpeed = (steps * speed / RAMP_UP);
		currentSpeed = this->getCurrentSpeedRPM();
		error = desiredSpeed - currentSpeed;
		Discrete_U.u = error;
		this->oneStep();
		outputInvolts = (Discrete_Y.y);
		duty = (outputInvolts * PWM_PER) / 7;
		this->setMotorDutyCycle((int)duty);
	}
	//steady
	else if (steps > RAMP_UP&& steps <= (RAMP_UP + RAMP_STEADY)) {}
	//decelerate
	else if (steps > (RAMP_UP + RAMP_STEADY) && steps <= (RAMP_UP + RAMP_STEADY + RAMP_DOWN)) {
		desiredSpeed = (((RAMP_UP + RAMP_STEADY + RAMP_DOWN) - steps) * speed) / RAMP_DOWN;
		currentSpeed = this->getCurrentSpeedRPM();
		error = desiredSpeed - currentSpeed;
		Discrete_U.u = error;
		this->oneStep();
		outputInvolts = (Discrete_Y.y);
		duty = (outputInvolts * PWM_PER) / 7;
		this->setMotorDutyCycle((int)duty);
	}
	//printf("steps: %d Ist-Speed: %d Soll-Speed: %d duty: %0.2f  \n", steps, currentSpeed, desiredSpeed, duty );
	if (steps >= 400) {
		this->myMotor->stopMotor();
		this->myMotor->setStatus(Stop);
		this->resetStepCounter();
	}
	return 0;
}

MotorState MotorController::getMotorState()
{
	return this->myMotor->getStatus();
}

int MotorController::setMotorState(MotorState state)
{
	int err = this->myMotor->setStatus(state);
	return err;
}

double MotorController::getCurrentSpeedRPM()
{
	return this->myMotor->getCurrentSpeed();
}

void MotorController::oneStep()
{
	myMotor->oneStep();
}

bool MotorController::readyToRecvPayload()
{
	// Check, if other thigs have to be tested
	if (myMotor->getStatus() == Stop) {
		return true;
	}
	return false;
}

 


