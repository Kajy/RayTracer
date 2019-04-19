//
// Created by xw on 19/04/19.
//

#ifndef RT_POINTLIGHT_HPP
#define RT_POINTLIGHT_HPP

#include <string>
#include <cmath>
#include "Config/config.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Debug/Debug.hpp"
#include <Objects/AShapeObject.hpp>

#ifdef _WIN32
#include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/vec3.hpp>
#endif

class PointLight : public AObject {
public:
    PointLight(double posX, double posY, double posZ);

    ~PointLight() = default;

};

#endif //RT_POINTLIGHT_HPP