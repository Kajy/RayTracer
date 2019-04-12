//
// Created by xw on 12/04/19.
//

#ifndef RT_WINDOW_HPP
#define RT_WINDOW_HPP

#include <memory>
#include <SDL2/SDL.h>

#include "Debug/Debug.hpp"

struct SDLWindowDeleter {
    inline void operator()(SDL_Window* window) {
        SDL_DestroyWindow(window);
    }
};

struct SDLRendererDeleter {
    inline void operator()(SDL_Renderer* renderer) {
        SDL_DestroyRenderer(renderer);
    }
};

class   Window {

public:
    Window(int w, int h);
    ~Window();

private:

    std::unique_ptr<SDL_Window, SDLWindowDeleter>       _window;
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter>   _renderer;

private:

    uint32_t    _width;
    uint32_t    _height;

};

#endif //RT_WINDOW_HPP
