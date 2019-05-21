//
// Created by Julian Vives on 2019-05-14.
//

#ifndef RT_BOX_HPP
#define RT_BOX_HPP


#include <Objects/AHitable.hpp>
#include <array>
#include <Objects/Triangle/Triangle.hpp>

class Box : public AHitable {
public:
    Box(const glm::dvec3 &tMin, const glm::dvec3 &tMax);

    Box(const glm::dvec3 &position, const glm::dvec3 &size, const Color &color, double refractionIndex, double shining);

    bool checkBounds(const glm::dvec3 &view, const glm::dvec3 &invDir) const;

    Intersection hit(const glm::dvec3 &view, const glm::dvec3 &vecDir, const glm::dvec3 &invDir) const override;

    glm::dvec3 calcNormal(const glm::dvec3 &hitPoint) const override;

private:
    glm::dvec3 _tMax;
    glm::dvec3 _tMin;
    std::vector<Triangle *> _triangles;
};


#endif //RT_BOX_HPP
