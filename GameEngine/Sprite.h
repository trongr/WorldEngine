#pragma once
#include <GL/glew.h>
#include <string>
#include "GLTexture.h"

namespace GameEngine {
    class Sprite
    {
    public:
        Sprite();
        Sprite(float x, float y, float width, float height, std::string texturepath);
        ~Sprite();
        void init(float x, float y, float width, float height, std::string texturepath);
        void draw();
    private:
        float _x, _y, _width, _height;
        GLuint _vboID;
        GLTexture _texture;
    };
}