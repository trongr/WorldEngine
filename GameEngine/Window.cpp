#include "Window.h"
#include "Errors.h"

namespace GameEngine {
    Window::Window()
    {
    }


    Window::~Window()
    {
    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags){

        Uint32 flags = SDL_WINDOW_OPENGL;

        if (currentFlags & INVISIBLE) flags |= SDL_WINDOW_HIDDEN;
        if (currentFlags & FULLSCREEN) flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        if (currentFlags & BORDERLESS) flags |= SDL_WINDOW_BORDERLESS;

        _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
        if (_sdlWindow == nullptr){
            fatalerror("couldn't create SDL window");
        }

        SDL_GLContext glcontext = SDL_GL_CreateContext(_sdlWindow);
        if (glcontext == nullptr){
            fatalerror("couldn't create SDL GL context");
        }

        //glewExperimental = true; // mk use this if glew crashes
        GLenum error = glewInit();
        if (error != GLEW_OK){
            fatalerror("couldn't init glew");
        }

        std::printf("*** OpenGL version %s ***\n", glGetString(GL_VERSION));

        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        SDL_GL_SetSwapInterval(1);

        return 0;
    }


    void Window::swapBuffer(){
        SDL_GL_SwapWindow(_sdlWindow);
    }

}