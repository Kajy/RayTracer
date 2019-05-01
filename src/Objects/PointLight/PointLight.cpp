//
// Created by xw on 13/04/19.
//

#include "PointLight.hpp"

PointLight::PointLight(double posX, double posY, double posZ) :
    ALight(glm::dvec3(posX, posY, posZ))
{

}

PointLight::PointLight(const glm::dvec3 &position) : ALight(position){

}