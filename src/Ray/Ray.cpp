//
// Created by xw on 18/04/19.
//

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

bool        Ray::launchRay(std::vector<AShapeObject *> const &shapeObjects)
{
    return (searchClosestHit(shapeObjects) > -1.0);
}

double      Ray::searchClosestHit(std::vector<AShapeObject *> const &shapeObjects) {

    double closestHit = -1.0;

    for (auto const &it: shapeObjects)
        glm::max(closestHit, it->calcCollision(_origin, _dir));
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