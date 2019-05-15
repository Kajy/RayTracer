//
// Created by Julian Vives on 2019-05-14.
//

#include <vector>
#include <Ray/Ray.hpp>
#include "Box.hpp"

Box::Box() : Box(glm::dvec3(0, 0, 0), glm::dvec3(1, 1, 1)) {
}

Box::Box(const glm::dvec3 &tMin, const glm::dvec3 &tMax) : AHitable(
        Color{255,0, 0, 255}, glm::dvec3(tMin.x + tMax.x / 2, tMin.y + tMax.y / 2, tMin.z + tMax.z / 2)), _tMin(tMin), _tMax(tMax) {
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
    _triangles.emplace_back(new Triangle(BOX_VERTICES[0], BOX_VERTICES[1], BOX_VERTICES[2]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[2], BOX_VERTICES[1], BOX_VERTICES[3]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[2], BOX_VERTICES[3], BOX_VERTICES[4]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[3], BOX_VERTICES[5]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[5], BOX_VERTICES[6]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[5], BOX_VERTICES[7]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[7], BOX_VERTICES[0]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[0], BOX_VERTICES[7], BOX_VERTICES[1]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[1], BOX_VERTICES[7], BOX_VERTICES[3]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[3], BOX_VERTICES[7], BOX_VERTICES[5]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[6], BOX_VERTICES[0], BOX_VERTICES[4]));
    _triangles.emplace_back(new Triangle(BOX_VERTICES[4], BOX_VERTICES[0], BOX_VERTICES[3]));
}

Intersection Box::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {

    for (auto &it: _triangles) {
        Intersection newHit = it->hit(view, vecDir);
        if (newHit.isHit) {
            return newHit;
        }
    }

    return Intersection();
}

glm::dvec3 Box::calcNormal(const glm::dvec3 &hitPoint) const {
    return glm::dvec3();
}
