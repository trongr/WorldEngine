#pragma once

#include <Windows.h>
#include <SDL/SDL.h>
#include <GL/glew.h>
#include <vector>

#include <GameEngine/GameEngine.h>
#include <GameEngine/Sprite.h>
#include <GameEngine/GLSLProgram.h>
#include <GameEngine/GLTexture.h>
#include <GameEngine/Window.h>

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
    GameEngine::Window _window;
    int _screenwidth;
    int _screenheight;
    GameState _gamestate;
    std::vector<GameEngine::Sprite*> _sprites;
    GameEngine::GLSLProgram _colorProgram;
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

