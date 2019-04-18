//
// Created by xw on 13/04/19.
//

#include "PointLight.hpp"

PointLight::PointLight(double x, double y, double z) : AObject(glm::dvec3(x, y, z))
{
}

PointLight::~PointLight()
{
}