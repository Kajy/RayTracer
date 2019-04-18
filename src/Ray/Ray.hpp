//
// Created by xw on 18/04/19.
//

#ifndef RT_RAY_HPP
#define RT_RAY_HPP

#include <vector>
#include "Objects/AShapeObject.hpp"

#ifdef _WIN32
    #include "gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/glm.hpp>
    #include <glm/detail/type_vec.hpp>
    #include <glm/vec3.hpp>
#endif

class   Ray {

public:
    Ray();
    Ray(glm::dvec3 const &origin, glm::dvec3 const &dir);
    ~Ray();

    Intersection        launchRay(std::vector<AShapeObject *> const &shapeObjects);
    Intersection        searchClosestHit(std::vector<AShapeObject *> const &shapeObjects);

    void        setDirection(double x, double y, double z);
    glm::dvec3  getDirection() const;

    void        setOrigin(double x, double y, double z);
    glm::dvec3  getOrigin() const;

private:
    glm::dvec3      _dir;
    glm::dvec3      _origin;

};

#endif //RT_RAY_HPP
