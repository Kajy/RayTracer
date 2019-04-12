//
// Created by xw on 12/04/19.
//

#ifndef RT_RAYTRACER_HPP
#define RT_RAYTRACER_HPP

#include <iostream>
#include <memory>

#include "Config/config.hpp"
#include "Window/Window.hpp"
#include "EventHandler/EventHandler.hpp"

class   RayTracer {

public:
    RayTracer();
    ~RayTracer();

    void    run();

private:
    Window         _window;
    EventHandler   _eventHandler;


};

#endif //RT_RAYTRACER_HPP
