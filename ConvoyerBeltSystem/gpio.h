/*
File: gpio.h
Author: HP
As of: 2919-10-17
*/

#ifndef GPIO_H_
#define GPIO_H_

#include "funcs.h"

#define GPIO_PATH "/sys/class/gpio"

/*
Struct: gpioDescriptor
gpioNum: Number to identify GPIO. Example: P8_12 (pin number on Beaglebone Black) 
         = GPIO1_12 (pin number of the processor): 32*1+12=44 (GPIO number of the software)
direction: "in" or "out" (C string)
*/
typedef struct {
	int gpioNum;
	char direction [4];
} gpioDescriptor;

/*
Struct: kbdDescriptor
contains descriptors of kbdOut0, kbdOut1, kbdOut2, kbdOut3 kbdIn0, kbdIn1, kbdIn2, kbdIn3;
*/
typedef struct {
	char version;
	gpioDescriptor kbdOut0;
	gpioDescriptor kbdOut1; 
	gpioDescriptor kbdOut2; 
	gpioDescriptor kbdOut3; 
	gpioDescriptor kbdIn0;
	gpioDescriptor kbdIn1;
	gpioDescriptor kbdIn2;
	gpioDescriptor kbdIn3;
} kbdDescriptor;

/*
Function: gpioOpen
Parameter: a struct of type gpioDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Since the all the gpios used by me are already enabled,
only the direction is set accordingly.
*/
extern int gpioOpen(gpioDescriptor* gpio);

/*
Function: gpioSetValue
Parameter: a struct of type gpioDescriptor, and the value (0 or 1)
Returns: 0 on succes, -1 on error, including error output
Does: Sets the output to the desired value
*/
extern int gpioSetValue(gpioDescriptor* gpio, int value);

/*
Function: gpioGetValue
Parameter: a struct of type gpioDescriptor
Returns: the value (0 or 1) or -1 on error, including error output
Does: Reads the input
*/
extern int gpioGetValue(gpioDescriptor* gpio);

/*
Function: initKeyboard
Parameter: a descriptor of type kbdDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Initializes the 4 inputs and the 4 outputs needed to scan the keyboard
Fills the struct kbdDescriptor with appropriate values
*/
extern int initKeyboard(kbdDescriptor* kbd);

/*
Function: getKey
Parameter: a descriptor of type kbdDescriptor
Returns: ASCII of key pressed, or 0x00 if no key was pressed
Does: Scans the keyboard, by setting the putputs to 0 one after the other and reading the inputs
*/
extern char getKey(kbdDescriptor* kbd);

#endif /* GPIO_H_ */
