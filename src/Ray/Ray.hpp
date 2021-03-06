//
// Created by xw on 18/04/19.
//

#ifndef RT_RAY_HPP
#define RT_RAY_HPP

#include <vector>
#include <iostream>
#include "Objects/AHitable.hpp"

#ifdef _WIN32
    #include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/glm.hpp>
    #include <glm/vec3.hpp>
#endif

class Ray {

public:
    Ray();
    Ray(glm::dvec3 const &origin, glm::dvec3 const &dir);
    ~Ray();

    Intersection        launchRay(std::vector<AHitable *> const &shapeObjects);
    Intersection        searchClosestHit(std::vector<AHitable *> const &shapeObjects);

    void        setDirection(double x, double y, double z);
    glm::dvec3  getDirection() const;

    void        setOrigin(double x, double y, double z);
    glm::dvec3  getOrigin() const;

private:
    glm::dvec3      _dir;
    glm::dvec3      _origin;
    glm::dvec3      _invDir;
};

#endif //RT_RAY_HPP
