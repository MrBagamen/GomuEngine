#include <gomu/gomu.hpp>
#include <gomu/input.hpp>
#include <gomu/Sprite.hpp>
#include <gomu/Text.hpp>
#include <gomu/Sound.hpp>
#include <gomu/Music.hpp>
#include <gomu/Shader.hpp>
#include <gomu/Timer.hpp>
#include <iostream>

struct Entity {
    gomu::Sprite sprite;
    double x = 64 , y = 128;
    int speed = 200;

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
        gomu::setBackgroundColor(51, 178, 51);
        ballTexture.loadFromFile("res/ball.png");
        stickTexture.loadFromFile("res/stick.png");
        ball.sprite.setTexture(ballTexture);
        stick.sprite.setTexture(stickTexture);
        font.openFromFile("res/fast99.ttf", 16);
        scoreText.setFont(font);
        scoreText.setString("Score: 0");
        fsText.setFont(font);
        fsText.setString("Fullscreen: off - Alt-enter to toggle");
        fsText.setPosition(0, 16);
        exText.setFont(font);
        fpsText.setFont(font);
        fpsText.setString("FPS: ");
        fpsText.setPosition(0, 32);
        exText.setString("Press Escape to exit");
        exText.setPosition(0, 48);

        sound1.loadFromFile("res/test.ogg");
        music.loadFromFile("res/aa_arofl.xm");
        music.play();
        srand(time(NULL));

        //Testing shaders
        shader.Load("test.vert", "test.frag");
        shader.enable(true);
    }

    void onKeyPress(SDL_Scancode key)
    {
        if (key == SDL_SCANCODE_RETURN && SDL_GetModState() & KMOD_LALT)
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
        if (key == SDL_SCANCODE_ESCAPE)
        {
            gomu::quit();
        }
    }

    void onUpdate(double dt)
    {
        if (gomu::isKeyDown(SDL_SCANCODE_LEFT))
        {
            ball.x -= (ball.speed * dt);
        }
        else if (gomu::isKeyDown(SDL_SCANCODE_RIGHT))
        {
            ball.x += (ball.speed * dt);
        }
        if (gomu::isKeyDown(SDL_SCANCODE_UP))
        {
            ball.y -= (ball.speed * dt);
        }
        else if (gomu::isKeyDown(SDL_SCANCODE_DOWN))
        {
            ball.y += (ball.speed * dt);
        }
        //Wrap when out of bounds
        if (ball.x >= 640)
        {
            ball.x = -32;
        }
        else if(ball.x+32 <= 0)
        {
            ball.x = 640;
        }
        else if(ball.y >= 480)
        {
            ball.y = -32;
        }
        else if(ball.y+32 <= 0)
        {
            ball.y = 480;
        }

        if (collision(ball, stick))
        {
            stick.x = rand() % (640 - 32);
            stick.y = rand() % (480 - 32);
            ++score;
            scoreText.setString("Score: " + std::to_string(score));
            sound1.play();
        }

        //Count FPS
        if(fpsTimer.getTicks() >= 1000)
        {
            fpsText.setString("FPS: " + std::to_string(FPS));
            FPS = 0;
            fpsTimer.start(); //Restart timer
        }
        FPS++;
    }

    void onDraw()
    {
        //shader.enable(true);
        ball.draw();
        //shader.enable(false);

        stick.draw();
        scoreText.draw();
        fsText.draw();
        exText.draw();
        fpsText.draw();
    }

    Entity ball, stick;
    int score = 0;
    gomu::Texture ballTexture, stickTexture;
    gomu::Font font;
    gomu::Text scoreText, fsText, exText;
    gomu::Sound sound1;
    gomu::Music music;
    gomu::Shader shader;
    gomu::Timer fpsTimer;
    gomu::Text fpsText;
    int FPS = 0;
};

int main()
{
    gomu::init(640, 480, false, "Pickin' Sticks");
    gomu::addState(new Sticks, "sticks");
    gomu::setState("sticks");
    return gomu::exec();
}
