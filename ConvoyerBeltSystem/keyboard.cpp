#include <stdio.h>
#include "keyboard.h"

int keyCount;
extern Keyboard* myKeyBoard;

Keyboard :: Keyboard() {
	printf("Keyboard Konstruktor!\n");	
	kbdd = new kbdDescriptor();
	initKeyboard(kbdd);
	return;
}

Keyboard :: ~Keyboard() {
	pressedKey = 0;
	return;
}

char Keyboard::getPressedKey( )
{

	char currentValue = getKey(kbdd);
	sleep(50);	// implement a more elegant way of sleep: maybe timer

	return currentValue;


}
