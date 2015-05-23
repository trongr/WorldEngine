#include <iostream>
#include <stdlib.h>
#include <SDL/SDL.h>
#include "Errors.h"

namespace GameEngine {
    void fatalerror(std::string errorstring){
        std::cout << errorstring << std::endl;
        std::cout << "enter any key to quit....\n";
        std::getchar();
        SDL_Quit();
        exit(1);
    }
}