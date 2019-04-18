//
// Created by xw on 12/04/19.
//

#ifndef RT_RAYTRACER_HPP
#define RT_RAYTRACER_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include <future>

#include "Config/config.hpp"
#include "Window/Window.hpp"
#include "EventHandler/EventHandler.hpp"
#include "Scene/Scene.hpp"

class   RayTracer {
public:
    RayTracer();
    ~RayTracer();

    static Scene   parse(const std::string &filename);
    void    run();

private:
    Window			_window;
    EventHandler	_eventHandler;
	Scene			_scene;
public:
    const Window &getWindow() const;

    const EventHandler &getEventHandler() const;

    void setEventHandler(const EventHandler &eventHandler);

    const Scene &getScene() const;

    void setScene(const Scene &scene);
};

#endif //RT_RAYTRACER_HPP
