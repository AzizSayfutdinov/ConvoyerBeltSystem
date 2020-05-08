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
