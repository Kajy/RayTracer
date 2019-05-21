//
// Created by xw on 12/04/19.
//

#ifndef RT_WINDOW_HPP
#define RT_WINDOW_HPP

#include <memory>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "Config/Configuration.hpp"
#include "Common/Intersection.hpp"
#include "Common/Debug.hpp"

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

struct SDLTextureDeleter {
    inline void operator()(SDL_Texture* texture) {
        SDL_DestroyTexture(texture);
    }
};

class   Window {

public:
    Window(int w, int h);
    ~Window();

    void    drawPixel(Color color, uint32_t x, uint32_t y) const;
    void    render() const;

private:

    std::unique_ptr<SDL_Window, SDLWindowDeleter>       _window;
public:
    const std::unique_ptr<SDL_Window, SDLWindowDeleter> &getWindow() const;

private:
    std::unique_ptr<SDL_Renderer, SDLRendererDeleter>   _renderer;
    std::unique_ptr<SDL_Texture, SDLTextureDeleter>     _texture;
public:
    const std::unique_ptr<SDL_Texture, SDLTextureDeleter> &getTexture() const;

public:
    const std::unique_ptr<SDL_Renderer, SDLRendererDeleter> &getRenderer() const;

private:

    uint32_t        _windowWidth;
    uint32_t        _windowHeight;
    int             _drawableSurfaceWidth;
    int             _drawableSurfaceHeight;
	float			_ratioW, _ratioH;

    Intersection    *_image;

public:
    int getDrawableSurfaceWidth() const;
    int getDrawableSurfaceHeight() const;

	uint32_t	getWidth() const;
	uint32_t	getHeight() const;

	float		getRatioW() const;
	float		getRatioH() const;


    Intersection *getImage() const;

};

#endif //RT_WINDOW_HPP
