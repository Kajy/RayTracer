//
// Created by xw on 12/04/19.
//

#include "RayTracer.hpp"

RayTracer::RayTracer():
    _window(WINDOW_W, WINDOW_H)
{
    Debug::printInfo("Welcome on the RayTracer of KJ.");
}

RayTracer::~RayTracer()
{
    Debug::printInfo("Bye !");
}

void    RayTracer::run()
{
    uint32_t width = _window.getDrawableSurfaceWidth();
    uint32_t height = _window.getDrawableSurfaceHeight();

    for (uint32_t x = 0; x < width; ++x) {
        for (uint32_t y = 0; y < height; ++y) {
            this->_window.drawPixel(WHITE_COLOR, x, y);
        }
    }
    this->_window.render();

    while (!(_eventHandler.mayClose())) {
        _eventHandler.wait();
        _eventHandler.manageWindowEvent();
    }
}