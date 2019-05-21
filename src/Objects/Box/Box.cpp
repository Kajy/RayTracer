//
// Created by Julian Vives on 2019-05-14.
//

#include <vector>
#include <Ray/Ray.hpp>
#include "Box.hpp"

Box::Box(const glm::dvec3 &tMin, const glm::dvec3 &tMax) : AHitable(
        Color{255,0, 0, 255}, glm::dvec3(tMin.x + tMax.x / 2, tMin.y + tMax.y / 2, tMin.z + tMax.z / 2)), _tMin(tMin), _tMax(tMax) {
}

Intersection Box::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir, const glm::dvec3 &invDir) const {

    Intersection  finalInter;

    if (_triangles.empty()) {
        if (checkBounds(view, invDir)) {
            finalInter.isHit = true;
            finalInter.color = Color(0,255,0,0);
            finalInter.distanceWithViewer = 0.1;
        }
    } else {
        for (auto &it: _triangles) {
            Intersection newHit = it->hit(view, vecDir, invDir);
            if (newHit.isHit && finalInter.distanceWithViewer > newHit.distanceWithViewer) {
                finalInter = newHit;
            }
        }
    }

    return finalInter;
}

glm::dvec3 Box::calcNormal(const glm::dvec3 &hitPoint) const {
    return glm::dvec3();
}

Box::Box(const glm::dvec3 &position, const glm::dvec3 &size, const Color &color, double refractionIndex, double shining) : AHitable(color, position),
_tMin(position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2),
_tMax(position.x + size.x / 2, position.y + size.y / 2, position.z + size.z / 2){
    glm::dvec3 tMin(position.x - size.x / 2, position.y - size.y / 2, position.z - size.z / 2);
    glm::dvec3 tMax(position.x + size.x / 2, position.y + size.y / 2, position.z + size.z / 2);

    const std::vector<glm::dvec3> BOX_VERTICES = {
            {tMin.x, tMin.y, tMax.z},
            {tMax.x, tMin.y, tMax.z},
            {tMin.x, tMax.y, tMax.z},
            {tMax.x, tMax.y, tMax.z},
            {tMin.x, tMax.y, tMin.z},
            {tMax.x, tMax.y, tMin.z},
            {tMin.x, tMin.y, tMin.z},
            {tMax.x, tMin.y, tMin.z},
    };
    _triangles.emplace_back(new Triangle(BOX_VERTICES[0], BOX_VERTICES[1], BOX_VERTICES[2], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[2], BOX_VERTICES[1], BOX_VERTICES[3], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[2], BOX_VERTICES[3], BOX_VERTICES[4], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[3], BOX_VERTICES[5], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[5], BOX_VERTICES[6], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[5], BOX_VERTICES[7], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[7], BOX_VERTICES[0], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[0], BOX_VERTICES[7], BOX_VERTICES[1], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[1], BOX_VERTICES[7], BOX_VERTICES[3], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[3], BOX_VERTICES[7], BOX_VERTICES[5], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[0], BOX_VERTICES[4], color, refractionIndex, shining));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[0], BOX_VERTICES[2], color, refractionIndex, shining));
}

bool Box::checkBounds(const glm::dvec3 &view, const glm::dvec3 &invDir) const {
    double t1 = (_tMin.x - view.x)*invDir.x;
    double t2 = (_tMax.x - view.x)*invDir.x;

    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    t1 = (_tMin.y - view.y)*invDir.y;
    t2 = (_tMax.y - view.y)*invDir.y;

    tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
    tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

    if (tmin > tmax || tmax < tmin)
        return false;

    t1 = (_tMin.z - view.z)*invDir.z;
    t2 = (_tMax.z - view.z)*invDir.z;

    tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
    tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

    return tmax > std::max(tmin, 0.0);
}
