#pragma once
#include <string>
#include "GLTexture.h"

namespace GameEngine {
    class ImageLoader
    {
    public:
        static GLTexture loadPNG(std::string filepath);
    };
}