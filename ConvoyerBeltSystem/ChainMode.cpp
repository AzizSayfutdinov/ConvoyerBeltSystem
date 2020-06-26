#include "ChainMode.h"

ChainMode::ChainMode():Mode()
{
	network = Network::getInstance();
}

ChainMode* ChainMode::getInstance()
{
	if (instance == nullptr) {
		instance = new ChainMode();
	}
	return instance;
}

Command* ChainMode::recv()
{
	return communication->parse();

}

void ChainMode::send(Command* command)
{
	network->send(command->data, command->dest);
}
