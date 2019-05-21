//
// Created by Julian Vives on 2019-05-07.
//

#ifndef RT_POLYGON_HPP
#define RT_POLYGON_HPP


#include <Objects/AHitable.hpp>
#include <Objects/Triangle/Triangle.hpp>
#include <vector>
#include <Objects/Box/Box.hpp>

class Polygon : public AHitable {
public:
    Polygon();
    Polygon(const std::vector<Triangle *> &triangles, const glm::dvec3 &tMin, const glm::dvec3 &tMax);
    ~Polygon() = default;

    glm::dvec3              calcNormal(const glm::dvec3 &hitPoint) const override;
    Intersection		    hit(const glm::dvec3 &view, const glm::dvec3 &vecDir, const glm::dvec3 &invDir) const override;

private:
    std::vector<Triangle *> _triangles;
    Box                     *_hitBox;
public:
    Box *getHitBox() const;
};


#endif //RT_POLYGON_HPP
