//
// Created by xw on 12/04/19.
//

#include "Window.hpp"

Window::Window(int w, int h):
    _height(h),
    _width(w)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Debug::printError("Init SDL failed !");
        SDL_Quit();
    }

    Debug::printSuccess("Init SDL Done.");

    _window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow("App Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0));

    if (_window == nullptr) {
        Debug::printError("Error when creating window.");
    }
}

Window::~Window() {
    SDL_DestroyWindow(_window.get());
    Debug::printInfo("SDL Window destroyed.");
}
