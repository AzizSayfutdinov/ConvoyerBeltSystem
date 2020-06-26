#include "LocalMode.h"

LocalMode::LocalMode():Mode()
{
	userInterface = UserInterface::getInstance();
	telnetServer = TelnetServer::getInstance();
}

LocalMode* LocalMode::getInstance()
{
	if (instance == nullptr) {
		instance = new LocalMode();
	}
	return instance;
}

LocalMode::~LocalMode()
{
	delete this;
}

Command* LocalMode::recv()
{
	communication->parse();

}

void LocalMode::send(Command* command)
{
	// possible send some data to telnet server
	telnetServer->sendData(command->data);
}

