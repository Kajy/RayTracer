//
// Created by Julian Vives on 2019-05-07.
//

#include "Polygon.hpp"

Polygon::Polygon() : AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)) {
}

Intersection Polygon::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {
    return Intersection();
}

glm::dvec3 Polygon::calcNormal(const glm::dvec3 &hitPoint) const {
    return glm::dvec3();
}
