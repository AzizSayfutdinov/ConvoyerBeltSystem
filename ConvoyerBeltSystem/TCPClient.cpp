#include "TCPClient.h"

TCPClient::TCPClient(in_addr_t serverAddress, int port)
{
    this->IPAddress = IPAddress;
    this->port = port;
    init();
}

TCPClient::TCPClient()
{
    init();
}

int TCPClient::init()
{

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cerr << "Socket creation error " << endl;
        return -1;
    }
    bzero(&serverAddr, sizeof(serverAddr));

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(RIGHT_CONVBELT_IP);
    serverAddr.sin_port = htons(TCP_PORT);

    // create worker thread
    thread* t = new thread(&TCPClient::connectToServer, this);

}

void TCPClient::connectToServer()
{

    cout << "Searching for server ... " << endl;

    int res = 1;
    while (res != 0) {
        res = connect(sock, (struct sockaddr*) & serverAddr, sizeof(serverAddr));
    }

    if (res < 0)
    {
        cerr << "Connection Failed " << endl;
        return;
    }

    thread* serverThread;
    serverThread = new thread(&TCPClient::threadServerHandler, this);

}

void TCPClient::sendData(string data)
{
    // convert string to char*
    char* toSend = new char[data.size() + 1];
    std::copy(data.begin(), data.end(), toSend);
    toSend[data.size()] = '\0'; // don't forget the terminating 0

    send(sock, toSend, strlen(toSend), 0);
    delete[] toSend;
}

void TCPClient::threadServerHandler()
{
    cout << "Connected with server" << endl;

    // Greet Server!
    cout << "Sending greeting to server" << endl;
    // char greeting[] = "Hi Server! This is a client ... ";
    // send(sock, greeting, sizeof(greeting) + 1, 0);

    while (true)
    {
        // empty buffer
        memset(buffer, 0, BUF_SIZE);

        // read balues and save in buffer
        recv(sock, buffer, BUF_SIZE, 0);

        // handle input from server = RIGHT
        handleServerInput();

    }
}

void TCPClient::handleServerInput()
{
    string input(buffer);

    // debug
    cout << "Received from Server (RIGHT): " << input << endl;

    // TODO: Check if currentMode == ChainMode
    // Maybe set communication to network when changing to ChainMode: NO, only makes sense if in chainmode only TCP is used
    // myConveyorBelt->currentMode->communication = ((ChainMode*)myConveyorBelt->currentMode)->network;

    // updateCommunicationType = true;
    // !!! Replave updateCom with a check, where the package is coming from: src

    if (input == "REQUEST\r\n" || input == "Request\r\n" || input == "request\r\n") {
        myStateMaschine->sendEvent("RecvCmdRequest");
    }
    else if (input == "RELEASE\r\n" || input == "Release\r\n" || input == "release\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdRelease");
    }
    else if (input == "READY\r\n" || input == "Ready\r\n" || input == "ready\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdReady");
    }
    else if (input == "WAIT\r\n" || input == "Wait\r\n" || input == "wait\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdWait");
    }
    else
    {
        // updateCommunicationType = false;
    }
}


