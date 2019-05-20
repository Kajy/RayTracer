//
// Created by Julian Vives on 2019-05-07.
//

#include "Polygon.hpp"

Polygon::Polygon() : AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)) {
}

Intersection Polygon::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir, const glm::dvec3 &invDir) const {
    Intersection finalInter;

    if (_hitBox->checkBounds(view, invDir)) {
        for (auto &triangle: _triangles) {
            Intersection hit = triangle->hit(view, vecDir, invDir);
            if (hit.isHit && finalInter.distanceWithViewer > hit.distanceWithViewer) {
                finalInter = hit;
            }
        }
    }

    return finalInter;
}

glm::dvec3 Polygon::calcNormal(const glm::dvec3 &hitPoint) const {
    return glm::dvec3();
}

Polygon::Polygon(const std::vector<Triangle *> &triangles, const glm::dvec3 &tMin, const glm::dvec3 &tMax)  :
    AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)),
    _triangles(triangles),
    _hitBox(new Box(tMin, tMax)){
}
