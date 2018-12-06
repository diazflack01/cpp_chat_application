#include "client.h"

#include <iostream>

#include <netdb.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

void listenerThread(const int communicationSocket, std::function<void(const char*)> callback)
{
    char buffer[1024];
    int bytesRead;

    while (1) {
        bzero(buffer, 1024);
        bytesRead = read(communicationSocket, buffer, 1024);
        if(bytesRead <= 0)
        {
            std::cout << "ERROR: " << bytesRead <<  " bytes read\n";
            std::cout << "errno - " << static_cast<int>(errno) << "\n";
            close(communicationSocket);
            return;
        }

        std::cout << bytesRead << " bytes received from SOCK[" << communicationSocket << "]\n";
        callback(buffer);
    }
}

Client::Client() : mIsConnected(false)
{
    mSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    if(-1 == mSocketFd)
    {
        std::cout << "Failed to create socket\n";
        return;
    }
}

bool Client::isConnected() const
{
    return mIsConnected;
}

bool Client::connectTo(const char *ip, const int port)
{
    mServerAddress.sin_family = AF_INET;
    mServerAddress.sin_port = htons(port);

    const auto host = gethostbyname(ip);
    bcopy((char *)host->h_addr, (char *)&mServerAddress.sin_addr.s_addr, host->h_length);

    const auto status = connect(mSocketFd, (const sockaddr*)&mServerAddress, sizeof(mServerAddress));

    if(status < 0)
    {
        std::cout << "Failed to connect\n";
        return false;
    }
    mIsConnected = true;
    return true;
}

void Client::startCommunication()
{
    //spawn reader thread
    spawnListenerThread();

    waitForInputLoop();
}

void Client::spawnListenerThread()
{
    mListernerThread = std::thread(listenerThread, mSocketFd, [&](const char* msg){ this->print(msg); });
}

void Client::print(const char* msg)
{
    std::cout << msg << "\n";
}

void Client::waitForInputLoop()
{
    std::string userMsg;
    int bytesSent;

    while (1) {
        std::getline(std::cin, userMsg);
        bytesSent = send(mSocketFd, userMsg.c_str(), userMsg.size(), 0);

        if(bytesSent <= 0)
        {
            std::cout << "ERROR: " << bytesSent <<  " bytes read\n";
            std::cout << "errno - " << static_cast<int>(errno) << "\n";
            close(mSocketFd);
            return;
        }

        std::cout << bytesSent << " bytes sent from SOCK[" << mSocketFd << "]\n";
    }
}
