#include "Network.h"

Network::Network()
{
	server = new TCPServer(HOST_IP, TCP_PORT);

}

Network* Network::getInstance()
{
	if (instance == nullptr) {
		instance = new Network();
	}
	return instance;
}

Command* Network::parse()
{
	Command* recvCommand = server->getCurrentCommand();

	if (recvCommand->src == SystemLocation::Master) {
		return recvCommand;
	}
	else if (recvCommand->src == SystemLocation::LeftConveyorBelt)
	{
		Command* cmd = new Command(to_string(server->requestBuffer), SystemLocation::LeftConveyorBelt, SystemLocation::Self);
		server->requestBuffer--;
		return cmd;

	}
	else
	{
		return new Command("", SystemLocation::NoLocation, SystemLocation::NoLocation);
	}

}

void Network::send(Command* cmd)
{
	switch (cmd->dest)
	{
	case RightConveyorBelt:
		rightConveyorBelt->sendData(cmd->data);
		break;
	case LeftConveyorBelt:
		server->sendData(cmd->data);
		break;
	default:
		break;
	}
}

void Network::send(string data, SystemLocation src, SystemLocation dest)
{
	switch (dest)
	{
	case RightConveyorBelt:
		rightConveyorBelt->sendData(data);
		break;
	case LeftConveyorBelt:
		server->sendData(data);
		break;
	default:
		break;
	}
}

void Network::send(string data, SystemLocation dest)
{
	switch (dest)
	{
	case RightConveyorBelt:
		rightConveyorBelt->sendData(data);
		break;
	case LeftConveyorBelt:
		server->sendData(data);
		break;
	default:
		break;
	}
}
