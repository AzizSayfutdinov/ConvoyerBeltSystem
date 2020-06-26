#pragma once
#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

extern "C" {
#include "cons.h"
};

class Display
{
public:
	Display();
	~Display();
	int displayLine(char* string);
	int displayClear();
private:
	char myConsoleName[MAX_FILENAME] = "ConveyorBeltConsole";
	consDescriptor* myConsole;
};

