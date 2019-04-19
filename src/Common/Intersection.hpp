//
// Created by xw on 18/04/19.
//

#ifndef RT_INTERSECTION_HPP
#define RT_INTERSECTION_HPP

#include "Config/config.hpp"
#include "Common/Color.hpp"

typedef struct   Intersection {

    Intersection(): distanceWithViewer(MAX_DISTANCE), color(0, 0, 0, 255) {}

    Color   color;
    double  distanceWithViewer;
} Intersection;

#endif //RT_INTERSECTION_HPP
