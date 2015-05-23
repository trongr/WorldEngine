#include <iostream>
#include "TextureCache.h"
#include "ImageLoader.h"

TextureCache::TextureCache()
{
}


TextureCache::~TextureCache()
{
}

GLTexture TextureCache::getTexture(std::string texturePath){
    auto it = _textureMap.find(texturePath);
    if (it == _textureMap.end()){
        GLTexture newTexture = ImageLoader::loadPNG(texturePath);
        std::pair<std::string, GLTexture> newPair(texturePath, newTexture);
        _textureMap.insert(newPair);
        std::cout << "caching new texture\n";
        return newTexture;
    } else {
        std::cout << "using cached texture\n";
        return it->second;
    }
}
