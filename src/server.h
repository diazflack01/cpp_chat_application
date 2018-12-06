#ifndef SERVER_H
#define SERVER_H

#include <vector>
#include <thread>
#include <functional>

#include <netinet/in.h>

using SocketDescriptor_t = int;

void listenerThread(const SocketDescriptor_t communicationSocket, std::function<void(const char*)> callback);

class Server
{
    SocketDescriptor_t mSocketFd;
    int mPortId;
    sockaddr_in address;
    std::vector<SocketDescriptor_t> mCommunicationSocketFd;
    std::vector<std::thread> mListenerThreads;

    void broadcast(const char* msg);
    void spawnListenerThread(const SocketDescriptor_t communicationSocket);
    void waitForConnectionLoop();

public:
    Server(const int port);
    void start();
};


#endif // SERVER_H
