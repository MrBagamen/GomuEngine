#include "window.hpp"
#include "DrawText.hpp"

int main()
{
    Window w;
    w.Create(1024, 768, "GomuEngine");
    DrawText::Init();

    //Test Drawin Text
    DrawText text1;
    text1.loadFont("res/fast99.ttf", 48);
    text1.textColor(255, 255, 0);
    text1.setText("This is first font!");
    text1.setPosition(32, 32);

    DrawText text2;
    text2.loadFont("res/stocky.ttf", 26);
    text2.textColor(0, 255, 0);
    text2.setText("This is second font!");
    text2.setPosition(32, 128);

    DrawText text3;
    text3.loadFont("res/valuoldcaps.ttf", 80);
    text3.textColor(100, 100, 255);
    text3.setText("This is third font!");
    text3.setPosition(32, 256);

    while(w.isRunning())
    {
        text1.Draw();
        text2.Draw();
        text3.Draw();

        w.Update();
    }

    return 0;
}

