#include "Mode.h"

Mode::Mode()
{
	motorController = new MotorController();
	receivedCommand = new Command();
	communication = UserInterface::getInstance();

}

