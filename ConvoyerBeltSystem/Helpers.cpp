#include "Helpers.h"

void sleep(double seconds) {

	clock_t startClock = clock();
	double secondsAhead = seconds * CLOCKS_PER_SEC;

	while (clock() < startClock + secondsAhead) {

	}

	return;
}