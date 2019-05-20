//
// Created by Julian Vives on 2019-04-22.
//

#ifndef RT_PLANE_HPP
#define RT_PLANE_HPP


#include <Objects/AHitable.hpp>

class Plane : public AHitable {
public:
    Plane();
    Intersection		hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const override;
    glm::dvec3          calcNormal(const glm::dvec3 &hitPoint) const override ;
    void                normalizePosition();

    ~Plane() = default;

private:
    double      _height;

public:
    double  getHeight() const;

    void	setHeight(double height);
};


#endif //RT_PLANE_HPP
