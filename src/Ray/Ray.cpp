//
// Created by xw on 18/04/19.
//

#include <Common/Intersection.hpp>
#include "Ray.hpp"


Ray::Ray() {

}

Ray::Ray(glm::dvec3 const &origin, glm::dvec3 const &dir):
    _origin(origin),
    _dir(dir),
    _invDir(1/dir.x, 1/dir.y, 1/dir.z)
{
}

Ray::~Ray() {

}


Intersection        Ray::launchRay(std::vector<AHitable *> const &shapeObjects)
{
    return searchClosestHit(shapeObjects);
}


Intersection      Ray::searchClosestHit(std::vector<AHitable *> const &shapeObjects) {

    Intersection    hit;
    uint32_t        idxObj = 0;

    for (auto const &it: shapeObjects) {
        Intersection newHit = it->hit(_origin, _dir, _invDir);
        if (newHit.distanceWithViewer < hit.distanceWithViewer) {
            hit = newHit;
        }
        ++idxObj;
    }

    return hit;
}

void        Ray::setDirection(double x, double y, double z) {
    _dir.x = x; _dir.y = y, _dir.z = z;
}

glm::dvec3  Ray::getDirection() const {
    return _dir;
}

void        Ray::setOrigin(double x, double y, double z) {
    _origin.x = x; _origin.y = y; _origin.z = z;
}

glm::dvec3  Ray::getOrigin() const {
    return _origin;
}