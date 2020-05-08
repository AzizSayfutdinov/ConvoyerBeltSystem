#pragma once
#include <iostream>
#include <cstdio>

using namespace std;

class Display
{
public:
	int display(string string);
	int displayLine(string string);	// with carriage return
	int display(int integerValue); 
	int display(double doubleValue);
};

