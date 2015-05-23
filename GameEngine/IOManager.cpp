#include <fstream>
#include "IOManager.h"

namespace GameEngine {
    bool IOManager::readFileToBuffer(std::string filepath, std::vector<unsigned char>& buffer){
        std::ifstream file(filepath, std::ios::binary);
        if (file.fail()){
            perror(filepath.c_str());
            return false;
        }

        // get file size
        file.seekg(0, std::ios::end);
        int filesize = file.tellg();
        file.seekg(0, std::ios::beg);
        filesize -= file.tellg(); // subtract size of file headers

        // read file to buffer
        buffer.resize(filesize);
        file.read((char*)&(buffer[0]), filesize);
        file.close();

        return true;
    }
}