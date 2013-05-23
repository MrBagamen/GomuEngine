#include <gomu/Application.hpp>
#include <gomu/Text.hpp>
#include <gomu/Sprite.hpp>
#include <gomu/State.hpp>
#include <gomu/input.hpp>

class Text : public gomu::State {
public:
    Text()
    {
        text1.loadFont("res/fast99.ttf", 48);
        text1.textColor(255, 255, 0);
        text1.setString("This is first font!");
        text1.setPosition(32, 32);


        text2.loadFont("res/stocky.ttf", 26);
        text2.textColor(0, 255, 0);
        text2.setString("This is second font!");
        text2.setPosition(32, 128);


        text3.loadFont("res/valuoldcaps.ttf", 80);
        text3.textColor(100, 100, 255);
        text3.setString("This is third font!");
        text3.setPosition(32, 256);

        sprite1.loadImage("res/test.png");
        sprite1.setPosition(32, 350);
        //sprite1.Color(255, 255, 0);
    }

    void onUpdate(double dt)
    {
        if (gomu::isKeyDown(SDLK_LEFT))
        {
            --angle;
        }

        else if (gomu::isKeyDown(SDLK_RIGHT))
        {
            ++angle;
        }

        sprite1.rotate(angle);
    }

    void onDraw()
    {
        text1.draw();
        text2.draw();
        text3.draw();

        sprite1.draw();
    }

    gomu::Text text1;
    gomu::Text text2;
    gomu::Text text3;
    gomu::Sprite sprite1;
    int angle = 0;
};

int main()
{
    gomu::Application app(1024, 768, "Gomu Gomu no... JETTO ENGINE!");
    app.addState(new Text(), "text");
    app.setState("text");
    return app.exec();
}

