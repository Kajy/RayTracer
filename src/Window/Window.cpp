//
// Created by xw on 12/04/19.
//

#include "Window.hpp"

Window::Window(int w, int h):
    _windowHeight(h),
    _windowWidth(w)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        Debug::printError("Init SDL failed !");
        SDL_Quit();
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::string error = std::string() + "Unable to Init hinting: " + SDL_GetError();
        Debug::printError(error.c_str());
    }
    Debug::printSuccess("Init SDL Done.");

    if ((_window = std::unique_ptr<SDL_Window, SDLWindowDeleter>(SDL_CreateWindow("App Name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _windowWidth, _windowHeight, SDL_WINDOW_ALLOW_HIGHDPI))) == nullptr) {
        Debug::printError("Error when creating window.");
    }

    SDL_GL_GetDrawableSize(_window.get(), &_drawableSurfaceWidth, &_drawableSurfaceHeight);

    if ((_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED))) == nullptr) {
        Debug::printError("Error when creating renderer");
    }
}

Window::~Window() {
    SDL_DestroyWindow(_window.get());
    Debug::printInfo("SDL Window destroyed.");
}


void        Window::drawPixel(uint32_t color, uint32_t x, uint32_t y) const
{
    SDL_SetRenderDrawColor(_renderer.get(), ((color & 0xff000000) >> 24), ((color & 0x00ff0000) >> 16), ((color & 0x0000ff00) >> 8), 255);
    SDL_RenderDrawPoint(_renderer.get(), x, y);
}

void        Window::render() const
{
    SDL_RenderPresent(_renderer.get());
}

int         Window::getDrawableSurfaceWidth() const {
    return _drawableSurfaceWidth;
}


int         Window::getDrawableSurfaceHeight() const {
    return _drawableSurfaceHeight;
}
