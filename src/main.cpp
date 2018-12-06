#include <iostream>

#include "server.h"

int main(int argc, char** argv)
{
    std::cout << "main\n";
    Server s(atoi(argv[1]));
    s.start();
    return 0;
}
