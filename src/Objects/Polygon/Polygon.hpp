//
// Created by Julian Vives on 2019-05-07.
//

#ifndef RT_POLYGON_HPP
#define RT_POLYGON_HPP


#include <Objects/AHitable.hpp>

class Polygon : public AHitable {
public:
    Polygon();
    ~Polygon() = default;

    glm::dvec3              calcNormal(const glm::dvec3 &hitPoint) const override;
    Intersection		    hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const override;
};


#endif //RT_POLYGON_HPP
