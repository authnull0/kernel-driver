#include <iostream>
#include "kernelInterface.hpp"

int main()
{
    kernelInterface Driver = kernelInterface("\\\\.\\kerneldriver");

    ULONG address = Driver.GetAddress();


    std::cout << address << std::endl;

    while (true) {
    }
}

