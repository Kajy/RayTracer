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

    if ((_window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow("App Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, 0))) == nullptr) {
        Debug::printError("Error when creating window.");
    }

    if ((_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(_window.get(), 0, SDL_RENDERER_ACCELERATED))) == nullptr) {
        Debug::printError("Error when creating renderer");
    }
}

Window::~Window() {
    SDL_DestroyWindow(_window.get());
    Debug::printInfo("SDL Window destroyed.");
}


void        Window::drawPixel(uint32_t color, uint32_t x, uint32_t y) const
{
    SDL_SetRenderDrawColor(_renderer.get(), ((color & 0xff000000) >> 24), ((color & 0x00ff0000) >> 16), ((color & 0x0000ff00) >> 8), 0);
    SDL_RenderDrawPoint(_renderer.get(), x, y);
}

void        Window::render() const
{
    SDL_RenderPresent(_renderer.get());
}