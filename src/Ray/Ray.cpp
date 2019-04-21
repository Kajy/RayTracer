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

Intersection        Ray::launchRay(std::vector<AHitable *> const &shapeObjects)
{
    return searchClosestHit(shapeObjects);
}

Intersection      Ray::searchClosestHit(std::vector<AHitable *> const &shapeObjects) {

    Intersection    hit;

    for (auto const &it: shapeObjects) {
        double newHitDistance = it->hit(_origin, _dir);
        if (newHitDistance > -1.0 && newHitDistance < hit.distanceWithViewer) {
            hit.distanceWithViewer = newHitDistance;
            hit.color = it->getColor();
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