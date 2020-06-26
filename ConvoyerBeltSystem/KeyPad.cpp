#include "KeyPad.h"

KeyPad::KeyPad()
{
	keyboard = new Keyboard();
	thread* keyPadThread = new thread(&KeyPad::handleKeyInput, this);
	
}

KeyPad::~KeyPad()
{
	delete this;
}

void KeyPad::handleKeyInput()
{
	while (true)
	{
		readValue = keyboard->getPressedKey();

		switch (readValue)
		{
		case '1':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdDirectionKeyPad");
			break;

		case '2':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdDirectionKeyPad");
			break;

		case'3':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdFollowProfile");	
			break;

		case '4':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdStopMotor");
			break;

		case '5':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdChain");
			break;

		case '6':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdLocal");
			break;

		case '7':
			lastValue = readValue;
			myStateMaschine->sendEvent("RecvCmdSetSpeedPoti");
			break;

		default:
			break;
		}
		usleep(150000);
	}
}

string KeyPad::readKey()
{
	return string(1, keyboard->getPressedKey());
}

char KeyPad::getLastKeyInput()
{
	return lastValue;
}
