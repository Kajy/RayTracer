//
// Created by xw on 12/04/19.
//

#ifndef RT_WINDOW_HPP
#define RT_WINDOW_HPP

#include <memory>
#include <SDL2/SDL.h>

#include "Common/Intersection.hpp"
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

    void    drawPixel(Color color, uint32_t x, uint32_t y) const;
    void    render() const;
    void    generateDistanceMap(double maxDist);

private:

    std::unique_ptr<SDL_Window, SDLWindowDeleter>       _window;
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter>   _renderer;

private:

    uint32_t        _windowWidth;
    uint32_t        _windowHeight;
    int             _drawableSurfaceWidth;
    int             _drawableSurfaceHeight;

    Intersection    *_image;
    Intersection    *_distanceMap;

public:
    int getDrawableSurfaceWidth() const;
    int getDrawableSurfaceHeight() const;

    Intersection *getImage() const;

};

#endif //RT_WINDOW_HPP
