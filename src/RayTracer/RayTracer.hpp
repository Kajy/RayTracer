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
#include <thread>

#include "Config/Configuration.hpp"
#include "Window/Window.hpp"
#include "EventHandler/EventHandler.hpp"
#include "Scene/Scene.hpp"

class   RayTracer {
public:
    RayTracer();
    RayTracer(const Configuration &configuration);
    ~RayTracer();

    Scene            parse(const std::string &filename);
    void    run();

private:
    Window			_window;
    EventHandler	_eventHandler;
	Scene			_scene;
	std::string     _filename;
    Configuration   _config;
public:
    const Configuration &getConfig() const;

    void setConfig(const Configuration &config);

public:
    const std::string &getFilename() const;

    void setFilename(const std::string &filename);

public:
    const Window &getWindow() const;

    const EventHandler &getEventHandler() const;

    void setEventHandler(const EventHandler &eventHandler);

    const Scene &getScene() const;

    void setScene(const Scene &scene);

    void renderLoop();
};

#endif //RT_RAYTRACER_HPP
