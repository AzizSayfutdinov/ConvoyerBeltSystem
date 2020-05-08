#include "Display.h"



int Display::display(string string)
{
	cout << string;
	cout.flush();
	return 0;
}

int Display::displayLine(string string)
{
	cout << string << endl;
	return 0;
}

int Display::display(int integerValue)
{
	cout << integerValue;
	cout.flush();
	return 0;
}

int Display::display(double doubleValue)
{
	cout << doubleValue;
	cout.flush();
	return 0;
}
