#include <gomu/gomu.hpp>
#include <gomu/DrawText.hpp>

int main()
{
    gomu::init(1024, 768, "GomuEngine");

    //Test Drawin Text
    DrawText text1;
    text1.loadFont("res/fast99.ttf", 48);
    text1.textColor(255, 255, 0);
    text1.setString("This is first font!");
    text1.setPosition(32, 32);

    DrawText text2;
    text2.loadFont("res/stocky.ttf", 26);
    text2.textColor(0, 255, 0);
    text2.setString("This is second font!");
    text2.setPosition(32, 128);

    DrawText text3;
    text3.loadFont("res/valuoldcaps.ttf", 80);
    text3.textColor(100, 100, 255);
    text3.setString("This is third font!");
    text3.setPosition(32, 256);

    bool running = true;

    while(running)
    {
        SDL_Event e;

        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                running = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        text1.draw();
        text2.draw();
        text3.draw();
        SDL_GL_SwapBuffers();
    }

    return 0;
}

