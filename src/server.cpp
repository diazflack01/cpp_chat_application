#include "server.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

void listenerThread(const SocketDescriptor_t communicationSocket, std::function<void(const char*)> callback)
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

Server::Server(const int port) : mPortId(port)
{
    mSocketFd = socket(AF_INET, SOCK_STREAM, 0);

    if(-1 == mSocketFd)
    {
        std::cout << "Failed to create socket\n";
        return;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(mPortId);

    if(bind(mSocketFd, (sockaddr*)(&address), sizeof(address)) < 0)
    {
        std::cout << "Failed to bind socket to port[" << mPortId << "]\n";
        return;
    }

    listen(mSocketFd, 3);
}
void Server::broadcast(const char* msg)
{
    std::cout << "Broadcasting...\n";

    for(const auto& client : mCommunicationSocketFd)
    {
        const auto bytesSent = send(client, msg, sizeof(msg), 0);
        std::cout << bytesSent << " bytes sent to SOCK[" << client << "]\n";
    }
}

void Server::spawnListenerThread(const SocketDescriptor_t communicationSocket)
{
    mListenerThreads.push_back(std::thread(listenerThread, communicationSocket,
                                           [&](const char* m)
    {
        broadcast(m);
    }));
}

void Server::waitForConnectionLoop()
{
    std::cout << "Waiting for connection...\n";
    sockaddr_in clientAddr;
    socklen_t sizeOfClientAddr = sizeof(clientAddr);
    SocketDescriptor_t communicationSocket;

    while (1) {
        communicationSocket = accept(mSocketFd, (sockaddr*)(&clientAddr), &sizeOfClientAddr);

        if(communicationSocket < 0)
        {
            std::cout << "Failed to accept connection\n";
            continue;
        }

        std::cout << "Got connection from[" << inet_ntoa(clientAddr.sin_addr) << "] port[" <<
                     ntohs(clientAddr.sin_port) << "]\n";

        mCommunicationSocketFd.push_back(communicationSocket);

        spawnListenerThread(communicationSocket);
    }
}

void Server::start()
{
    waitForConnectionLoop();
}
