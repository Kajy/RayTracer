//
// Created by xw on 18/04/19.
//

#ifndef RT_INTERSECTION_HPP
#define RT_INTERSECTION_HPP

#include <glm/vec3.hpp>

#include "Config/config.hpp"
#include "Common/Color.hpp"

typedef struct   Intersection {

    Intersection(): distanceWithViewer(MAX_DISTANCE), color(0, 0, 0, 255), isHit(false) {}

    Color       color;
    double      distanceWithViewer;
    glm::dvec3  hitPosition;
    glm::dvec3  normal;

    bool        isHit;

} Intersection;

#endif //RT_INTERSECTION_HPP
