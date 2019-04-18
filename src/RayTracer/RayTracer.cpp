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
    std::size_t max = width * height;
    uint32_t cores = std::thread::hardware_concurrency();
    std::vector<std::future<void>> future_vector;

    auto start = std::chrono::steady_clock::now();
    for (uint32_t i = 0; i < cores; ++i) {
      future_vector.emplace_back(std::async(std::launch::async, [=]() {
            for (std::size_t index(i); index < max; index += cores) {
                uint32_t x = index % width;
                uint32_t y = index / width;
                if (this->_scene.renderScene(x, y)) {
                    this->_window.drawPixel(WHITE_COLOR, x, y);
                } else {
                    this->_window.drawPixel(BLACK_COLOR, x, y);
                }
            }
        }));
    }

   /* for (uint32_t x = 0; x < WINDOW_W; ++x) {
        for (uint32_t y = 0; y < WINDOW_H; ++y) {
            if (this->_ray.launchRay(x, y, this->_scene)) {
                this->_window.drawPixel(WHITE_COLOR, x, y);
            } else {
                this->_window.drawPixel(BLACK_COLOR, x, y);
            }
        }
    }*/
    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in microseconds : "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " µs" << std::endl;
    std::cout << "Elapsed time in miliseconds : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    this->_window.render();

    while (!(_eventHandler.mayClose())) {
        _eventHandler.wait();
        _eventHandler.manageWindowEvent();
    }
}