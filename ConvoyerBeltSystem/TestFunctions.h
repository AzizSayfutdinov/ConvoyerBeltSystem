#pragma once
#include <string>
#include <string.h>
#include <chrono>
#include <thread>

#include "TCPServer.h"
#include "Display.h"
#include "TelnetServer.h"
#include "TCPClient.h"
#include "keyboard.h"
#include "LocalMode.h"
#include "ChainMode.h"

//#include "gpio.h"
//#include "spi.h"
//#include "pwm.h"

extern "C" {
#include "gpio.h"
#include "spi.h"
#include "pwm.h"
}

using namespace std;

// Should be implemented: Maybe try TDD (test driven development)
void testTCPServer();		// test with socketTest tool: address 192.168.7.2 with port 5555
void testDisplay();			// shows some possible output of motor state
void testTelnet();			// test with CMD line: telnet 192.168.7.2 4444
void testTCPClient();		// test with socketTest tool: listen to 192.168.7.1 address with port 5555
void testKeyPad();
void testPotentiometer();
void testMotor(int dir);
void testKeyBoard();
void testAbstractOverriddenFct();
void testClassFunctionPointer();
void testNormalFunctionPointer();
void testTableEntryWithFunctionPointer();
void testSMwihMemberFctFpointers();
void noAction();


