#include "Command.h"

string Command::getData()
{
	return data;
}

string Command::getSrc()
{
	return src;
}

string Command::getDest()
{
	return dest;
}

void Command::setData(string data)
{
	this->data = data;
}

void Command::setSrc(string src)
{
	this->src = src;
}

void Command::setDest(string dest)
{
	this->dest = dest;
}

Command::Command(string data, string src, string dest)
{
	this->data = data; 
	this->src = src; 
	this->dest = dest; 
}

Command::Command()
{
}

Command::~Command()
{
	delete this;
}
