//
// Created by xw on 18/04/19.
//

#include <Common/Intersection.hpp>
#include "Ray.hpp"


Ray::Ray() {

}

Ray::Ray(glm::dvec3 const &origin, glm::dvec3 const &dir):
    _origin(origin),
    _dir(dir)
{

}

Ray::~Ray() {

}

Intersection    Ray::launchRay(std::vector<AShapeObject *> const &shapeObjects)
{
    return searchClosestHit(shapeObjects);
}

Intersection    Ray::searchClosestHit(std::vector<AShapeObject *> const &shapeObjects) {

    Intersection    hit;

    for (auto const &it: shapeObjects) {
        Intersection newHit = it->calcCollision(_origin, _dir);
        if (newHit.distanceWithViewer < hit.distanceWithViewer) {
            hit = newHit;
            hit.normal = it->calcNormal(glm::dvec3(_origin + _dir * hit.distanceWithViewer));
        }
    }

    return (hit);
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