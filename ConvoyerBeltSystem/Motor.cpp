#include "Motor.h"

Motor::Motor()
{
	myEncoder = new Encoder();
	myController = new Controller();

	//Create instances for hardware usage
	this->IN1 = new gpioDescriptor;
	this->pwmMotor = new pwmDescriptor;
	this->spiDescMotor = new spiDescriptor;
	this->bridgeEN = new gpioDescriptor;
	this->bridgeDIS = new gpioDescriptor;

	initMotor();
}

Motor::Motor(Encoder* encoder, Controller* controller) : myEncoder(encoder), myController(controller)
{
	//Create instances for hardware usage
	this->IN1 = new gpioDescriptor;
	this->pwmMotor = new pwmDescriptor;
	this->spiDescMotor = new spiDescriptor;
	this->bridgeEN = new gpioDescriptor;
	this->bridgeDIS = new gpioDescriptor;
}

Motor::~Motor()
{
	delete this;
}

int Motor::initMotor()
{
	this->bridgeEN->gpioNum = 79;
	strcpy(this->bridgeEN->direction, "out");
	this->bridgeDIS->gpioNum = 76;
	strcpy(this->bridgeDIS->direction, "out");

	gpioOpen(this->bridgeEN);
	if (gpioSetValue(this->bridgeEN, 1) < 0) return -1;
	gpioOpen(this->bridgeDIS);
	if (gpioSetValue(this->bridgeDIS, 0) < 0) return -1;
	
	spiPinmux spiMotor;
	spiPinmux& spiMotorRef = spiMotor;
	strcpy(spiMotorRef.CSpin, "P9_28_pinmux");
	strcpy(spiMotorRef.MISOpin, "P9_29_pinmux");
	strcpy(spiMotorRef.MOSIpin, "P9_30_pinmux");
	strcpy(spiMotorRef.SCLKpin, "P9_31_pinmux");

	this->spiDescMotor->spiNum = 2;
	this->spiDescMotor->bitsPerWord = 8;
	this->spiDescMotor->mode = 1;
	this->spiDescMotor->flags = O_RDWR;
	this->spiDescMotor->speed = 1000000;
	this->spiDescMotor->pinmux = spiMotorRef;

	if (spiSetPinmux(this->spiDescMotor) < 0) return -1;
	if (spiOpen(this->spiDescMotor) < 0) return -1;

	spiXfer16Bits(this->spiDescMotor, 0xED18);
	usleep(50);
	this->readBackValSPI = spiXfer16Bits(this->spiDescMotor, 0x6D18);

	this->IN1->gpioNum = 22;
	strcpy(this->IN1->direction, "out");
	if (gpioOpen(this->IN1) < 0) return -1;
	//default direction: 
	if (gpioSetValue(this->IN1, 1) < 0) return -1;

	strcpy(this->pwmMotor->pinNameB, "P8_13_pinmux");
	this->pwmMotor->pwmNum = 7;
	if (pwmSetPinmux_B(this->pwmMotor) < 0) return -1;
	if (pwmOpen_B(this->pwmMotor) < 0) return -1;
	if (pwmSetPeriod_B(this->pwmMotor, 50000) < 0) return -1;
	//if (pwmSetDuty_B(this->pwmMotor, 0)) return -1;
	if (pwmSetPolarity_B(this->pwmMotor, 0)) return -1;
	return 0;
}

int Motor::setSpeedRPM(int speed)
{
	if (speed >= 100 && speed <= 2200) {
		this->speed = speed;
		return 0;
	}
	else {
		this->speed = 0;
		//printf("speed should be between 100 - 2200!\n");
		return 0;
	}
}

int Motor::getSpeed()
{
	return this->speed;
}

int Motor::setDutyCycle(int duty)
{
	int err; 
	if (duty < 0) {
		err = pwmSetDuty_B(this->pwmMotor, (0.01 * PWM_PER));
	}
	else
	{	
		err = pwmSetDuty_B(this->pwmMotor, duty);
	}
	return err;
}

int Motor::startMotor(bool direction)
{	
	if (direction == 0) {
		gpioSetValue(this->IN1, 1);
		pwmSetDuty_B(this->pwmMotor, this->speed * PWM_PER / MAX_SPEED_RPM);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->state = movingRight;
		return 1;
	}
	else if (direction == 1) {
		gpioSetValue(this->IN1, 0);
		pwmSetDuty_B(this->pwmMotor, this->speed * PWM_PER / MAX_SPEED_RPM);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->state = movingLeft;
		return 1;
	}
	else return -1;
}

int Motor::startMotor(bool direction, int speed)
{
	if (direction == 0) {
		gpioSetValue(this->IN1, 1);
		pwmSetDuty_B(this->pwmMotor, speed * PWM_PER / MAX_SPEED_RPM);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->state = movingRight;
		return 1;
	}
	else if (direction == 1) {
		gpioSetValue(this->IN1, 0);
		pwmSetDuty_B(this->pwmMotor, speed * PWM_PER / MAX_SPEED_RPM);
		pwmSetEnable_B(this->pwmMotor, 1);
		this->state = movingLeft;
		return 1;
	}
	else return -1;
}

int Motor::stopMotor()
{
	if (pwmSetEnable_B(this->pwmMotor, 0) < 0) return -1;
	return 0;
}

MotorState Motor::setStatus(MotorState motorstate)
{
	return (this->state = motorstate);
}

MotorState Motor::getStatus()
{
	return this->state;
}

double Motor::getCurrentSpeed()
{
	return this->myEncoder->getSpeedRPM();
}

void Motor::oneStep()
{	
	myController->oneStep();
}

int Motor::setDirection(Direction direction)
{	
	this->direction = direction;
	int err = 0; 
	if (direction == Right) {
		if(gpioSetValue(this->IN1, 1) < 0) return err;
	}
	else if (direction == Left) {
		if(gpioSetValue(this->IN1, 0) < 0) return err;
	}
	return err;
}

Direction Motor::getDirection()
{
	return this->direction;
}
