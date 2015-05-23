#pragma once
#include <vector>
#include <string>

namespace GameEngine {
    class IOManager
    {
    public:
        static bool readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer);
    };
}