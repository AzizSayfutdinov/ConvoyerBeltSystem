#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(HOST_IP, TELNET_PORT);
	// delete thread
	// thread* telnetThread = new thread(&TelnetServer::handleUserInput, this);
}

TelnetServer* TelnetServer::getInstance()
{
	if (instance == nullptr) {
		instance = new TelnetServer();
	}
	return instance;
}

Command* TelnetServer::parse()
{
	Command* receivedCommand = new Command(telnetServer->dataBuffer, TelnetUser, Self);

	//if (telnetServer->updateCommunicationType) {
	//	receivedCommand = new Command(telnetServer->buffer, TelnetUser, Self);
	//}
	//else {
	//	receivedCommand = new Command("", NoLocation, NoLocation);
	//}
	return receivedCommand;

}

void TelnetServer::send(Command* cmd)
{
	telnetServer->sendData(cmd->data);
}

void TelnetServer::sendData(string data)
{
	telnetServer->sendData(data);
}
