//
// Created by xw on 12/04/19.
//

#include <SDL2/SDL_image.h>
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

    if ((_renderer = std::unique_ptr<SDL_Renderer, SDLRendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE))) == nullptr) {
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

static void savePNG(SDL_Texture *texture, uint32_t *pixels, uint32_t w, uint32_t h)
{
    Uint32 format_pixels;
    SDL_QueryTexture(texture, &format_pixels, NULL, NULL, NULL);
    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, w, h, 32, w * sizeof(Uint32), format_pixels);
    IMG_SavePNG(surface, "scene.png");
    SDL_FreeSurface(surface);
}

void        Window::render() const
{

    SDL_Renderer *renderer = _renderer.get();
    void *tmp;
    Uint32 *pixels;
    int pitch;
    SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
                                _drawableSurfaceWidth, _drawableSurfaceHeight);
    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    SDL_LockTexture(texture, NULL, &tmp, &pitch);
    pixels = static_cast<Uint32 *>(tmp);

    for (uint32_t x = 0; x < _drawableSurfaceWidth; ++x) {
        for (uint32_t y = 0; y < _drawableSurfaceHeight; ++y) {
            Color color = _image[y * _drawableSurfaceWidth + x].color;
            pixels[y * _drawableSurfaceWidth + x] = SDL_MapRGBA(format, color.red, color.blue, color.green, color.alpha);
        }
    }

    SDL_FreeFormat(format);
    SDL_UnlockTexture(texture);
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    savePNG(texture, pixels, _drawableSurfaceWidth, _drawableSurfaceHeight);
    SDL_DestroyTexture(texture);
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

const std::unique_ptr<SDL_Window, SDLWindowDeleter> &Window::getWindow() const {
    return _window;
}

const std::unique_ptr<SDL_Renderer, SDLRendererDeleter> &Window::getRenderer() const {
    return _renderer;
}

const std::unique_ptr<SDL_Texture, SDLTextureDeleter> &Window::getTexture() const {
    return _texture;
}
