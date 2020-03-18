#include "State/MenuState.hpp"

#ifdef _WIN32
#include <windows.h>
#endif // _WIN32

#ifdef unix
#include <cstdio>
#endif // _UNIX

int main(int argc, char** argv)
{
    try
    {
        Application app;
        app.pushState(std::make_unique<State::MenuState>(app));
        app.mainLoop();
    }
    catch(const std::runtime_error& e)
    {
        #ifdef _WIN32
        MessageBox(nullptr, e.what(), "Runtime error", MB_OK);
        #endif // _WIN32

        #ifdef unix
        printf("Runtime error: %s\n", e.what());
        #endif // unix
    }

    return 0;
}
