#include <cstdio>
#include "MotorController.h"
#include "ConveyorBelt.h"
#include "StateManager.h"

using namespace std;

// predefine static variables for local and chain mode
LocalMode* LocalMode::instance = LocalMode::getInstance();
ChainMode* ChainMode::instance = ChainMode::getInstance();
TelnetServer* TelnetServer::instance = TelnetServer::getInstance();
UserInterface* UserInterface::instance = UserInterface::getInstance();
Network* Network::instance = Network::getInstance();

int main()
{

    StateManager* sm = new StateManager();
    sm->init();
    sm->startStateMaschine();

    return 0;
}
