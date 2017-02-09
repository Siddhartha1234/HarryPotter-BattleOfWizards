#include "Window.hpp"
#include "Errors.hpp"
namespace GameEngine {
    Window:: Window() {


    }
    Window::~Window() {

    }
    int Window::create(std::string windowName , int _screenWidth , int _screenHeight , unsigned int currentFlags) {

        Uint32 flags = SDL_WINDOW_OPENGL;

        if(currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }

        if(currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if(currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }
        _sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, flags);

        if(_sdlWindow == nullptr){
            fatalError("SDL Window could not be created!");
        }

        SDL_GLContext glContext= SDL_GL_CreateContext(_sdlWindow);

        if(glContext == nullptr){
            fatalError("SDL_GL Context could not be created!");
        }

        GLenum glewError= glewInit();
        if(glewError != GLEW_OK){
            fatalError("glew could not be initialized!");
        }


        glClearColor(0.0f,0.0f,0.0f,1.0f);

        SDL_GL_SetSwapInterval(0);

        return 0;
    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(_sdlWindow);
    }
}
