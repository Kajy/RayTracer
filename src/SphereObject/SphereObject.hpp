//
// Created by xw on 13/04/19.
//

#ifndef RT_SPHEREOBJECT_HPP
#define RT_SPHEREOBJECT_HPP

#include <string>
#include "Config/config.hpp"
#include "Camera/Camera.hpp"
#include "Debug/Debug.hpp"
#include "gtx/norm.hpp"

class SphereObject
{
public:
	SphereObject();
	SphereObject(double posX, double posY, double posZ, double radius);
	~SphereObject();

	double		isCollinding(glm::dvec3 view, glm::dvec3 vecDir) const;

private:

	glm::dvec3	_pos;
	double		_radius;

};

#endif //RT_SPHEREOBJECT_HPP