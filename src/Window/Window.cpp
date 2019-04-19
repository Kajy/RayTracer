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

    _image = new Intersection[_drawableSurfaceHeight * _drawableSurfaceWidth];
    _distanceMap = new Intersection[_drawableSurfaceHeight * _drawableSurfaceWidth];

    if ((_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED))) == nullptr) {
        Debug::printError("Error when creating renderer");
    }
}

Window::~Window() {
    SDL_DestroyWindow(_window.get());
    delete _image;
    Debug::printInfo("SDL Window destroyed.");
}


void        Window::drawPixel(Intersection inter, uint32_t x, uint32_t y) const
{
    _image[y * _drawableSurfaceWidth + x].color.red = inter.color.red;
    _image[y * _drawableSurfaceWidth + x].color.green = inter.color.green;
    _image[y * _drawableSurfaceWidth + x].color.blue = inter.color.blue;
    _image[y * _drawableSurfaceWidth + x].color.alpha = 255;
    _image[y * _drawableSurfaceWidth + x].distanceWithViewer = inter.distanceWithViewer;
}

void        Window::render() const
{
    for (uint32_t x = 0; x < _drawableSurfaceWidth; ++x) {
        for (uint32_t y = 0; y < _drawableSurfaceHeight; ++y) {
            Color color = _image[y * _drawableSurfaceWidth + x].color;
            SDL_SetRenderDrawColor(_renderer.get(), color.red, color.green, color.blue, 255);
            SDL_RenderDrawPoint(_renderer.get(), x, y);
        }
    }
    SDL_RenderPresent(_renderer.get());
}

void        Window::generateDistanceMap(double maxDist) {
    std::cout << "Max distance : " << maxDist << std::endl;
    for (uint32_t x = 0; x < _drawableSurfaceWidth; ++x) {
        for (uint32_t y = 0; y < _drawableSurfaceHeight; ++y) {
            double hitDist = glm::min(_image[y * _drawableSurfaceWidth + x].distanceWithViewer, maxDist);
            _distanceMap[y * _drawableSurfaceWidth + x].color.red = (unsigned char)((hitDist / maxDist) * 255);
            _distanceMap[y * _drawableSurfaceWidth + x].color.green = (unsigned char)((hitDist / maxDist) * 255);
            _distanceMap[y * _drawableSurfaceWidth + x].color.blue = (unsigned char)((hitDist / maxDist) * 255);
        }
    }
}

int         Window::getDrawableSurfaceWidth() const {
    return _drawableSurfaceWidth;
}


int         Window::getDrawableSurfaceHeight() const {
    return _drawableSurfaceHeight;
}

Intersection    *Window::getImage() const {
    return _image;
}
