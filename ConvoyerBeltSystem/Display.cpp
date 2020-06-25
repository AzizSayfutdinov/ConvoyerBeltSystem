#include "Display.h"

Display::Display()
{
	// printf("Display Construktor!\n");
	this->myConsole = new consDescriptor();
	strncpy(myConsole->fileName, this->myConsoleName, MAX_FILENAME);
	openConsole(myConsole);
}

Display::~Display()
{
	closeConsole(this->myConsole);
	delete this;
}

int Display::displayLine(char* string)
{
	if (writeLineToConsole(this->myConsole, string) < 0) 
		return -1;
	return 0;
}

int Display::displayClear()
{
	if (clearConsole(this->myConsole) < 0) 
		return -1;
	return 0;
}