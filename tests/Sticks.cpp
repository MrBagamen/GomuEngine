#include <gomu/Application.hpp>
#include <gomu/input.hpp>
#include <gomu/Sprite.hpp>
#include <gomu/Text.hpp>

struct Entity {
    gomu::Sprite sprite;
    int x = 0 , y = 0;
    void draw()
    {
        sprite.setPosition(x, y);
        sprite.draw();
    }
};

bool collision(const Entity& e1, const Entity& e2)
{
    return e1.x + 32 > e2.x && e1.y + 32 > e2.y && e1.x < e2.x + 32 && e1.y < e2.y + 32;
}

class Sticks : public gomu::State
{
public:

    Sticks()
    {
        glClearColor(0.2f, 0.7f, 0.2f, 1.0f);
        ballTexture.loadFromFile("res/ball.png");
        stickTexture.loadFromFile("res/stick.png");
        ball.sprite.setTexture(ballTexture);
        stick.sprite.setTexture(stickTexture);
        stick2.sprite.setTexture(stickTexture);
        stick2.x = 100;
        stick2.y = 100;
        font.openFromFile("res/fast99.ttf", 16);
        scoreText.setFont(font);
        scoreText.setString("Score: 0");
        fsText.setFont(font);
        fsText.setString("Fullscreen: off - Alt-enter to toggle");
        fsText.setPosition(0, 16);
    }

    void onKeyPress(SDLKey key)
    {
        if (key == SDLK_RETURN && SDL_GetModState() & KMOD_LALT)
        {
            if (gomu::toggleFullscreen())
            {
                fsText.setString("Fullscreen: on - Alt-enter to toggle");
            }
            else
            {
                fsText.setString("Fullscreen: off - Alt-enter to toggle");
            }
        }
    }

    void onUpdate(double dt)
    {
        if (gomu::isKeyDown(SDLK_LEFT))
        {
            ball.x -= 4;
        }
        else if (gomu::isKeyDown(SDLK_RIGHT))
        {
            ball.x += 4;
        }
        if (gomu::isKeyDown(SDLK_UP))
        {
            ball.y -= 4;
        }
        else if (gomu::isKeyDown(SDLK_DOWN))
        {
            ball.y += 4;
        }

        stick2.x = rand() % (640 - 32);
        stick2.y = rand() % (480 - 32);

        if (collision(ball, stick))
        {
            stick.x = rand() % (640 - 32);
            stick.y = rand() % (480 - 32);
            ++score;
            scoreText.setString("Score: " + std::to_string(score));
        }
    }

    void onDraw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        ball.draw();
        stick.draw();
        stick2.sprite.color(rand(), rand(), rand());
        stick2.draw();
        scoreText.draw();
        fsText.draw();
    }

    Entity ball, stick, stick2;
    int score = 0;
    gomu::Texture ballTexture, stickTexture;
    gomu::Font font;
    gomu::Text scoreText, fsText;
};

int main()
{
    gomu::Application app(640, 480, false, "Pickin' Sticks");
    app.addState(new Sticks, "sticks");
    app.setState("sticks");
    return app.exec();
}
