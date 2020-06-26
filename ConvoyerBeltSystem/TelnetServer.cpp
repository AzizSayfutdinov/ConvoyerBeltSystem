#include "TelnetServer.h"

TelnetServer::TelnetServer()
{
	telnetServer = new TCPServer(HOST_IP, TELNET_PORT);
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
