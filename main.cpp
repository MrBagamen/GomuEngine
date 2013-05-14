#include "window.hpp"

int main()
{
    Window w;
    w.Create(1024, 768, "GomuEngine");

    while(w.isRunning())
    {

        w.Update();
    }

    return 0;
}

