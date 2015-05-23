#pragma once

#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>
#include "Sprite.h"
#include "GLSLProgram.h"
#include "GLTexture.h"

enum class GameState {
    PLAY, EXIT
};

class Game
{
public:
    Game();
    ~Game();
    void run();

private:
    SDL_Window* _window;
    int _screenwidth;
    int _screenheight;
    GameState _gamestate;
    std::vector<Sprite*> _sprites;
    GLSLProgram _colorProgram;
    float _time;
    float _fps;
    float _maxFPS;
    float _frameTime;

    void init();
    void loop();
    void input();
    void draw();
    void initShaders();
    void calFPS();
    void printFPS(int interval);
};

