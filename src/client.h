#ifndef CLIENT_H
#define CLIENT_H

#include <thread>

#include <netinet/in.h>

class Client
{
    int mSocketFd;
    int mPortId;
    bool mIsConnected;
    sockaddr_in mServerAddress;
    std::thread mListernerThread;

    void spawnListenerThread();
    void waitForInputLoop();
    void print(const char* msg);

public:
    Client();
    bool connectTo(const char* ip, const int port);
    void startCommunication();
    bool isConnected() const;
};

#endif // CLIENT_H
