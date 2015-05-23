#include <iostream>
#include <cstddef>
#include <string>
#include "Sprite.h"
#include "Vertex.h"
#include "ResourceManager.h"

Sprite::Sprite()
{
    _vboID = 0;
}

Sprite::Sprite(float x, float y, float width, float height, std::string texturepath)
{
    _vboID = 0;
    init(x, y, width, height, texturepath);
}

Sprite::~Sprite()
{
    if (_vboID != 0){
        glDeleteBuffers(1, &_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height, std::string texturepath){

    _x = x;
    _y = y;
    _width = width;
    _height = height;

    _texture = ResourceManager::getTexture(texturepath);

    if (_vboID == 0){
        glGenBuffers(1, &_vboID);
    }

    Vertex vertexData[6];

    // normalized device coordinates
    // normalized device coordinates
    // normalized device coordinates

    // first triangle

    vertexData[0].setPosition(x, y); // bottom left
    vertexData[0].setUV(0.0f, 0.0f);

    vertexData[1].setPosition(x, y + height); // top left
    vertexData[1].setUV(0.0f, 1.0f);

    vertexData[2].setPosition(x + width, y); // bottom right
    vertexData[2].setUV(1.0f, 0.0f);

    // second triangle

    vertexData[3].setPosition(x + width, y); // bottom right
    vertexData[3].setUV(1.0f, 0.0f);

    vertexData[4].setPosition(x, y + height); // top left
    vertexData[4].setUV(0.0f, 1.0f);

    vertexData[5].setPosition(x + width, y + height); // top right
    vertexData[5].setUV(1.0f, 1.0f);

    for (int i = 0; i < 6; i++){
        vertexData[i].setColor(255, 0, 255, 255);
    }

    vertexData[1].setColor(0, 255, 0, 255);
    vertexData[4].setColor(0, 0, 255, 255);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw(){

    // TODO track bound texture
    glBindTexture(GL_TEXTURE_2D, _texture.id);

    glBindBuffer(GL_ARRAY_BUFFER, _vboID);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    // 6 vertices
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}