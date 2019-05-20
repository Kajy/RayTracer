//
// Created by xw on 12/04/19.
//

#include <fstream>
#include <nlohmann/json.hpp>
#include "RayTracer.hpp"
#include <Common/Parser.hpp>
#include <Objects/ALight.hpp>
#include <Common/Utils.hpp>
#include <Objects/Plane/Plane.hpp>
#include <Objects/Box/Box.hpp>

using namespace nlohmann;

RayTracer::RayTracer():
    _window(WINDOW_W, WINDOW_H)
{
    Debug::printInfo("Welcome on the RayTracer of KJ.");
}

RayTracer::RayTracer(const Configuration &configuration):
    _window((int)configuration.resolution.width, (int)configuration.resolution.height),
    _config(configuration)
{
    Debug::printInfo("Welcome on the RayTracer of KJ.");
}

RayTracer::~RayTracer()
{
    Debug::printInfo("Bye !");
}

void    RayTracer::renderLoop()
{
    uint32_t width = _window.getDrawableSurfaceWidth();
    uint32_t height = _window.getDrawableSurfaceHeight();
    std::size_t max = width * height;
    uint32_t cores = std::thread::hardware_concurrency();
    std::vector<std::future<void>> future_vector;

    auto start = std::chrono::steady_clock::now();
    for (uint32_t i = 0; i < cores; ++i) {
        future_vector.emplace_back(std::async(std::launch::async, [=]() {
            for (uint32_t index(i); index < max; index += cores) {
                uint32_t x = index % width;
                uint32_t y = index / width;
                this->_window.drawPixel(this->_scene.renderScene(x, y, width, height, _config.antiAliasing), x, y);
            }
        }));
    }
    for (uint32_t i = 0; i < cores; ++i)
        future_vector[i].wait();

    auto end = std::chrono::steady_clock::now();
    std::cout << "Elapsed time in microseconds : "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
              << " µs" << std::endl;
    std::cout << "Elapsed time in miliseconds : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
              << " ms" << std::endl;

    this->_window.render();
}

void    RayTracer::run()
{
    this->renderLoop();
    while (!(_eventHandler.mayClose())) {
        _eventHandler.wait();
        _eventHandler.manageWindowEvent();
    }
}

const Window &RayTracer::getWindow() const {
    return _window;
}

const EventHandler &RayTracer::getEventHandler() const {
    return _eventHandler;
}

void RayTracer::setEventHandler(const EventHandler &eventHandler) {
    _eventHandler = eventHandler;
}

const Scene &RayTracer::getScene() const {
    return _scene;
}

void RayTracer::setScene(const Scene &scene) {
    _scene = scene;
}

void parseCamera(Scene &scene, const json &json, const Configuration &config, const Resolution &drawableSize) {
    Camera camera = Parser::ParseCamera(json["camera"], config, drawableSize);
    scene.setView(camera);
}

void parseObjects(Scene &scene, const json &jsonFile) {
    std::vector<AHitable *> objectsParsed;

    for (const json &object: jsonFile["objects"]) {
        const std::string &type = object["type"].get<std::string>();
        Debug::printInfo((std::string("PARSING OBJECT : ") + type).c_str());
        switch (Utils::str2int(type.c_str())) {
            case Utils::str2int("sphere"): {
                Sphere *sphere = Parser::ParseSphere(object);
                objectsParsed.push_back(sphere);
                Debug::printPosition(sphere, "sphere");
                break;
            }
            case Utils::str2int("plane"): {
                Plane *plane = Parser::ParsePlane(object);
                objectsParsed.push_back(plane);
                Debug::printPosition(plane, "plane");
                break;
            }
            case Utils::str2int("polygon"): {
                std::vector<Triangle *> triangles = Parser::ParseObj(object);
                objectsParsed.insert(std::end(objectsParsed), std::begin(triangles), std::end(triangles));
                break;
            }
            case Utils::str2int("box"): {
                Box *box = Parser::ParseBox(object);
                objectsParsed.emplace_back(box);
                break;
            }

        }
    }
    scene.setHitableObjects(objectsParsed);
}

void parseLights(Scene &scene, const json &jsonFile) {
    std::vector<ALight *>   lightsParsed;

    for (const json &objectLight : jsonFile["lights"]) {
        const std::string &type = objectLight["type"].get<std::string>();
        Debug::printInfo((std::string("PARSING LIGHT : ") + type).c_str());
        switch (Utils::str2int(type.c_str())) {
            case Utils::str2int("point"):
                lightsParsed.push_back(Parser::ParseLight<PointLight>(objectLight));
                break;
        }
    }

    scene.setLights(lightsParsed);
}

Scene RayTracer::parse(const std::string &filename) {
    std::vector<AHitable>   objectArr;

    std::ifstream           sceneFile(filename);
    json                    jsonScene;
    Scene                   scene;

    try {
        sceneFile >> jsonScene;
    } catch (nlohmann::detail::parse_error &e) {
        Debug::printError(e.what());
        Debug::printError("Exit");
        std::exit(1);
    }

    parseCamera(scene, jsonScene, this->_config, Resolution {
        (double)this->_window.getDrawableSurfaceWidth(),
        (double)this->_window.getDrawableSurfaceHeight()});
    parseObjects(scene, jsonScene);
    parseLights(scene, jsonScene);

    return scene;
}

const std::string &RayTracer::getFilename() const {
    return _filename;
}

void RayTracer::setFilename(const std::string &filename) {
    _filename = filename;
}

const Configuration &RayTracer::getConfig() const {
    return _config;
}

void RayTracer::setConfig(const Configuration &config) {
    _config = config;
}
