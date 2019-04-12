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
    for (uint32_t x = 0; x < WINDOW_W; ++x) {
        for (uint32_t y = 0; y < WINDOW_H; ++y) {
            this->_window.drawPixel(0xFFFFFFFF, x, y);
        }
    }
    this->_window.render();

    while (!(_eventHandler.mayClose())) {
        _eventHandler.wait();
        _eventHandler.manageWindowEvent();


    }
}