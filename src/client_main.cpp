#include <iostream>

#include "ui_mainwindow.h"
#include "client.h"

int main(int argc, char** argv)
{
    std::cout << "main\n";
    Client c;
    c.connectTo(argv[1], atoi(argv[2]));
    if(!c.isConnected())
    {
        std::cout << "Unable to connect to host\n";
    }
    c.startCommunication();

    return 0;
}
