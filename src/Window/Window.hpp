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

class   Window {

public:
    Window(int w, int h);
    ~Window();

private:

    //SDL_Window *_window;
    std::unique_ptr<SDL_Window, SDLWindowDeleter> _window;

private:

    uint32_t    _width;
    uint32_t    _height;

};

#endif //RT_WINDOW_HPP
