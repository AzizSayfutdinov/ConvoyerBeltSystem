#include "TCPClient.h"

Command* TCPClient::getCurrentCommand()
{
    Command* cmd = currentCommand;
    currentCommand = new Command("", SystemLocation::NoLocation, SystemLocation::NoLocation);
    return cmd;
}

TCPClient::TCPClient(in_addr_t serverAddress, int port)
{
    this->IPAddress = IPAddress;
    this->port = port;
    init();
}

TCPClient::TCPClient(char* IPAddress, int port)
{
    this->IPAddress = inet_addr(IPAddress);
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

    int c = 0;

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
    // cout << "Sending greeting to server" << endl;
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

    if (input == "Request\r\n") {
        myStateMaschine->sendEvent("RecvCmdRequest");
    }
    else if (input == "Release\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdRelease");
    }
    else if (input == "Ready\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdReady");
    }
    else if (input == "Wait\r\n")
    {
        myStateMaschine->sendEvent("RecvCmdWait");
    }
    else
    {

    }
}


