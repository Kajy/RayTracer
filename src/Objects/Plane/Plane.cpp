//
// Created by Julian Vives on 2019-04-22.
//

#include <glm/geometric.hpp>
#include "Plane.hpp"

Plane::Plane() : AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)) {

}

Intersection        Plane::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {
    Intersection    hit;

    if (vecDir.z != 0.000001) {
        double k = - ((_position.x * view.x) + (_position.y * view.y) + (_position.z * view.z) - _height) / (_position.x * vecDir.x + _position.y * vecDir.y + _position.z * vecDir.z);
        if (k > 0) {
            hit.color = _color;
            hit.distanceWithViewer = k;
            hit.hitPosition = view + vecDir * k;
            hit.isHit = true;
            hit.normal = _position;
            return hit;
        }
    }
    hit.isHit = false;
    return hit;
}

void    Plane::normalizePosition() {
    _position = glm::normalize(_position);
}

double Plane::getHeight() const {
    return _height;
}

void Plane::setHeight(double height) {
    _height = height;
}

glm::dvec3 Plane::calcNormal(const glm::dvec3 &hitPoint) const {
    return glm::normalize(_position);
}
