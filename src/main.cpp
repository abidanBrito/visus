// #include <Windows.h>
#include "App.hpp"
#include <iostream>

int main()
{
    // MessageBox(NULL, "Hey, sailor!", "Win32 MessageBox", MB_OK);
    // std::cout << "hey!!" << std::endl;
    std::unique_ptr<App> visusApp = std::make_unique<App>();
    visusApp->frameloop();

    return 0;
}
