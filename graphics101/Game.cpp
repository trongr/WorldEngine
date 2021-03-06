#define NOMINMAX
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstdio>
#include <algorithm>
#include <GameEngine/Errors.h>
#include "Game.h"

Game::Game() : 
    _screenwidth(1024), 
    _screenheight(720), 
    _gamestate(GameState::PLAY),
    _time(0),
    _maxFPS(60)
{

}


Game::~Game()
{
}

void Game::run(){
    init();

    std::string texturePath = "Textures/jimmyJump_pack/PNG/CharacterRight_Standing.png";
    _sprites.push_back(new GameEngine::Sprite(-1.0f, -1.0f, 1.0f, 1.0f, texturePath));
    _sprites.push_back(new GameEngine::Sprite(0.0f, -1.0f, 1.0f, 1.0f, texturePath));
    _sprites.push_back(new GameEngine::Sprite(-1.0f, 0.0f, 1.0f, 1.0f, texturePath));

    loop();
}

void Game::init(){

    _window.create("Game Engine", _screenwidth, _screenheight, GameEngine::FULLSCREEN);

    initShaders();
}

void Game::loop(){
    while (_gamestate != GameState::EXIT){
        float startTicks = SDL_GetTicks();

        input();
        _time += 0.01f;
        draw();
        calFPS();
        printFPS(10);

        // limit FPS to _maxFPS by waiting if this frame rendered faster than max FPS
        float delta = SDL_GetTicks() - startTicks;
        float delay = 1000.0f / _maxFPS - delta;
        if (delay > 0){
            SDL_Delay(delay);
        }
    }
}

// prints the FPS every interval ms
void Game::printFPS(int interval){
    static int frameCounter = 0;
    if (frameCounter == interval){
        std::cout << _fps << std::endl;
        frameCounter = 0;
    }
    frameCounter++;
}

void Game::input(){
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            _gamestate = GameState::EXIT;
            break;
        case SDL_MOUSEMOTION:
            //printf("%d %d\n", event.motion.x, event.motion.y);
            break;
        default:
            printf("Unhandled Event!\n");
            break;
        }
    }
}

void Game::draw(){
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _colorProgram.use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    GLuint timeLocation = _colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, _time);

    for (int i = 0; i < _sprites.size(); i++){
        _sprites[i]->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    _colorProgram.unuse();

    _window.swapBuffer();
}

void Game::initShaders(){
    _colorProgram.compileshaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
    _colorProgram.addAttr("vertexPosition");
    _colorProgram.addAttr("vertexColor");
    _colorProgram.addAttr("vertexUV");
    _colorProgram.linkshaders();
}

void Game::calFPS(){
    static const int NUM_SAMPLES = 10; // number of frames to average
    static int frameTimesIndex = 0;
    static float frameTimes[NUM_SAMPLES]; // buffer of the last NUM_SAMPLE frame times

    static float prevTicks = SDL_GetTicks();
    float curTicks = SDL_GetTicks();
    _frameTime = curTicks - prevTicks; // how long it took the last frame to play
    frameTimes[frameTimesIndex++ % NUM_SAMPLES] = _frameTime;

    float frameTimeAvg = 0;
    static int count = 0;
    count = std::max(count, NUM_SAMPLES);
    for (int i = 0; i < count; i++){
        frameTimeAvg += frameTimes[i];
    }
    frameTimeAvg = frameTimeAvg / count;

    if (frameTimeAvg > 0){
        _fps = 1000.0f / frameTimeAvg;
    } else {
        _fps = 60.0f;
    }

    prevTicks = curTicks;
}