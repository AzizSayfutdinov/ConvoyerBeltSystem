#include "MotorController.h"

int MotorController::followProfile(int direction)
{
	printf("Action: following Profile with direction &d", direction);
	return 0;
}

int MotorController::setSpeed(double speed)
{
	printf("Action: Speed set to %f", speed);
	return 0;
}

double MotorController::getCurrentSpeed(void)
{
	return currentSpeed;
}
