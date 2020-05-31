#include "LocalMode.h"

LocalMode::LocalMode()
{
}

int LocalMode::recv()
{
	cout << "LocalMode recv() function ... " << endl;
	return 0;
}

void LocalMode::testAction()
{
	cout << "Calling testAction from LocalMode with function pointer" << endl;
}

void LocalMode::idleAction()
{
	cout << "LocalMode performing idleAction ... " << endl;
}

void LocalMode::startAction()
{
	cout << "LocalMode performing startAction ... " << endl;
}

void LocalMode::runningAction()
{
	cout << "LocalMode performing runningAction ... " << endl;
}
