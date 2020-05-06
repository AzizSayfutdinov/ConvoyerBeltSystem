#include "TestFunctions.h"
#include <cstdio>

void testTCPServer()
{
	TCPServer* server = new TCPServer(inet_addr(HOST_IP), TCP_PORT);

	while (1) {}
}

void testDisplay()
{
	Display* d = new Display();

	int motorNumber1 = 1;
	int motorNumber2 = 2;
	double speed1 = 200.455;
	double speed2 = 300.595;

	// HEADLINE
	d->displayLine("MOTOR SPEEDS");
	d->displayLine("");	// used as line feed

	// speed motor 1
	d->display("Speed of motor ");
	d->display(motorNumber1);
	d->display(": ");
	d->display(speed1);
	d->displayLine(" rms! ");

	// speed motor 1
	d->display("Speed of motor ");
	d->display(motorNumber2);
	d->display(": ");
	d->display(speed2);
	d->displayLine(" rms! ");

	while (1) {}
}

void testTelnet()
{
	TelnetServer* telnetServer = new TelnetServer();

	while (1) {}
}

void testTCPClient()
{
	TCPClient* client = new TCPClient(inet_addr(RIGHT_CONVBELT_IP), TCP_PORT);

	while (1){}
}

void testMotor(int dir)
{
	/*
	Connection information:
	H-bridge pin IN1 is tied to pwm7 pin A (P8_19).
	H-bridge pin IN2 is tied to pwm7 pin B (P8_13).
	H-bridge pin DIS is tied to GPIO2_12 (P8_39) = 76 (GPIO SW-number).
	H-bridge pin ENBL is tied to GPIO2_15 (P8_38) = 79 (GPIO SW-number).
	*/
	/*
	When ENBL is logic HIGH, the H-Bridge is operational.When ENBL is logic LOW, the H-Bridge outputs are tri-stated and placed in Sleep mode.
	*/
	int retVal = 0;
	unsigned short readBackValSPI = 0;

	gpioDescriptor* bridgeEN = new gpioDescriptor; //(gpioDescriptor*)malloc(sizeof(gpioDescriptor));
	bridgeEN->gpioNum = 79;
	strcpy(bridgeEN->direction, "out");
	/*
	When DIS is logic HIGH, both OUT1 and OUT2 are tri-stated
	*/
	gpioDescriptor* bridgeDIS = new gpioDescriptor;
	bridgeDIS->gpioNum = 76;
	strcpy(bridgeDIS->direction, "out");

	gpioOpen(bridgeEN);
	retVal = gpioSetValue(bridgeEN, 1);
	gpioOpen(bridgeDIS);
	retVal = gpioSetValue(bridgeDIS, 0);

	retVal = gpioGetValue(bridgeEN);

	spiPinmux spiMotor;
	spiPinmux& spiMotorRef = spiMotor;
	strcpy(spiMotorRef.CSpin, "P9_28_pinmux");
	strcpy(spiMotorRef.MISOpin, "P9_29_pinmux");
	strcpy(spiMotorRef.MOSIpin, "P9_30_pinmux");
	strcpy(spiMotorRef.SCLKpin, "P9_31_pinmux");
	/*
	strcpy(spiMotor->CSpin, "P9_28_pinmux");
	strcpy(spiMotor->MISOpin, "P9_29_pinmux");
	strcpy(spiMotor->MOSIpin, "P9_30_pinmux");
	strcpy(spiMotor->SCLKpin, "P9_31_pinmux");
	*/
	spiDescriptor* spiDescMotor = new spiDescriptor;
	spiDescMotor->spiNum = 2;
	spiDescMotor->bitsPerWord = 8;
	spiDescMotor->mode = 1;
	spiDescMotor->flags = 2;
	spiDescMotor->speed = 10e6; // ???...
	spiDescMotor->pinmux = spiMotor;

	retVal = spiSetPinmux(spiDescMotor);
	retVal = spiOpen(spiDescMotor);
	
	//readBackValSPI = spiXfer16Bits(spiDescMotor, 0x0);
	readBackValSPI = spiXfer16Bits(spiDescMotor, 0xFD98);
	readBackValSPI = spiXfer16Bits(spiDescMotor, 0x7D98);
	while (true);

	/*
	IN1, IN2: Logic input control of OUT1, OUT2
	Code example Pilsan:
	pwmDescriptor* pwm = (pwmDescriptor*)malloc(sizeof(pwmDescriptor));
	strcpy(pwm->pinNameA, "P8_19_pinmux");
	strcpy(pwm->pinNameB, "P8_13_pinmux");
	pwm->pwmNum = 7;
	*/
}

void testKeyBoard()
{
	Keyboard* k = new Keyboard();
	char readValue;

	while (true) {
		readValue = k->getPressedKey();
		cout << "Key pressed: " << readValue << endl;
		this_thread::sleep_for(chrono::milliseconds(150));
	}

}

void testSMProfile()
{
	SpeedProfile* sp = new SpeedProfile();
	//TableEntry* tb = new TableEntry("a", "b", "c", 1, (void*)sp->addTableEntry, (void*)sp->addTableEntry);
	//TableEntry* tb2 = new TableEntry("a", "b", "c", 1, (void*)sp->addTableEntry, (void*)sp->addTableEntry);
	//TableEntry* tb3 = new TableEntry("a", "b", "c", 1, (void*)sp->addTableEntry, (void*)sp->addTableEntry);
	//sp->addTableEntry(tb);
	//sp->addTableEntry(tb2);
	//sp->addTableEntry(tb3);
	sp->removeLastTableEntry();
}

void testAbstractOverriddenFct()
{
	//LocalMode* lm = new LocalMode();
	//ChainMode* cm = new ChainMode();
	//lm->recv();
	//cm->recv();
}
