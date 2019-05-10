//
// Created by xw on 19/04/19.
//

#ifndef RT_POINTLIGHT_HPP
#define RT_POINTLIGHT_HPP

#include <string>
#include <cmath>
#include "Config/Configuration.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Common/Debug.hpp"
#include <Objects/AHitable.hpp>
#include <Objects/ALight.hpp>

#ifdef _WIN32
#include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/vec3.hpp>
#include <Objects/ALight.hpp>

#endif

class PointLight : public ALight {
public:
    PointLight(double posX, double posY, double posZ);
    PointLight(const glm::dvec3 &position);
    ~PointLight() = default;

};

#endif //RT_POINTLIGHT_HPP