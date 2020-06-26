#include "UserInterface.h"

UserInterface::UserInterface()
{
	keyPad = new KeyPad();
	potentiometer = new Potentiometer();
}

UserInterface* UserInterface::getInstance()
{
	if (instance == nullptr) {
		instance = new UserInterface();
	}
	return instance;
}

UserInterface::~UserInterface()
{
	delete this;
}

Command* UserInterface::parse()
{
	Command* receivedCommand = new Command();
	// KeyPad
	receivedCommand->data = keyPad->getLastKeyInput();
	receivedCommand->src = KeyPadLocal;
	receivedCommand->dest = Self;

	if (keyPad->getLastKeyInput() == '7') {	
		receivedCommand->data = to_string(potentiometer->getSpeed());
		receivedCommand->data = to_string(potentiometer->getSpeed());
		receivedCommand->src = PotentiometerLocal;
	}
	else if (keyPad->getLastKeyInput() == '1') {	// dir = right
		receivedCommand->data = "right";
	} 
	else if (keyPad->getLastKeyInput() == '2') {
		receivedCommand->data = "left";
	}
	return receivedCommand;
}

void UserInterface::send(Command* cmd)
{
	// not avaiable
}

