#include <gomu/gomu.hpp>
#include <gomu/Text.hpp>
#include <gomu/Sprite.hpp>
#include <gomu/State.hpp>
#include <gomu/input.hpp>

class Text : public gomu::State {
public:
    Text()
    {
        font1.openFromFile("res/fast99.ttf", 48);
        font2.openFromFile("res/stocky.ttf", 26);
        font3.openFromFile("res/valuoldcaps.ttf", 80);
        text1.setFont(font1);
        text2.setFont(font2);
        text3.setFont(font3);
        text1.setColor(255, 255, 0);
        text1.setString("This is first font!");
        text1.setPosition(32, 32);
        text2.setColor(0, 255, 0);
        text2.setString("This is second font!");
        text2.setPosition(32, 128);
        text3.setColor(100, 100, 255);
        text3.setString("This is third font!");
        text3.setPosition(32, 256);
    }

    void onDraw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        text1.draw();
        text2.draw();
        text3.draw();
    }

    gomu::Font font1, font2, font3;
    gomu::Text text1, text2, text3;
};

int main()
{
    gomu::init(1024, 768, false, "Font rendering test");
    gomu::addState(new Text(), "text");
    gomu::setState("text");
    return gomu::exec();
}

