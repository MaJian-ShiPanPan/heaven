#include <iostream>
#include <WinSock2.h>
#include <Windows.h>

int main(int argc, char* argv[])
{
    union
    {
        short s;
        char c[sizeof(short)];
    }uc;
    
    uc.s = 0x0102;
    if(1 == uc.c[0] && 2 == uc.c[1])
    {
        std::cout << "big-endin" << std::endl;
    }
    else if(2 == uc.c[0] && 1 == uc.c[1])
    {
        std::cout << "little-endin" << std::endl;
    }
    else
    {
        std::cout << "unKnow" << std::endl;
    }
    return 0;
}