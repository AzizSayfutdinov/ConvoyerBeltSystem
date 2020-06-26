/*
File: cons.h
Author: HP
As of: 2919-10-17
*/

#ifndef CONS_H_
#define CONS_H_

#include "funcs.h"
#include <stdio.h>

// #define MAX_CONS_LEN 80
#define MAX_CONS_LEN 200
#define MAX_CONS_HIGH 23

/* 
Operation information:
By using these functions the information is written into a file.
By default the file is written into the start directory of a remote shell, which is /home/debian
This file can be displayed by using the shell command "tail -f fileName"
*/

/*
Struct: consDescriptor
myFd: here the file descriptor is stored, after the file is opened.
fileName: name of the file. Has to be supplied before opening the file.
*/
typedef struct {
	FILE* myFd;
	char fileName[MAX_FILENAME];
} consDescriptor;

/*
Function: openConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Opens a file named "conssoleFile.txt" in the project directory
*/
extern int openConsole(consDescriptor* cons);

/*
Function: clearConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Clears the console for displaying new info
*/
extern int clearConsole(consDescriptor* cons);

/*
Function: writeLineToConsole
Parameter: a struct of type consDescriptor and a pointer to the string to be written
Returns: 0 on succes, -1 on error, including error output
Does: Writes the given string and moves to the next line
The maximum lenght is given by MAX_CONS_LEN
*/
extern int writeLineToConsole (consDescriptor* cons, char * myString);

/*
Function: closeConsole
Parameter: a struct of type consDescriptor
Returns: 0 on succes, -1 on error, including error output
Does: Closes the file "conssoleFile.txt"
*/
extern int closeConsole(consDescriptor* cons);

#endif /* CONS_H_ */
