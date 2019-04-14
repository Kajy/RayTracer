//
// Created by xw on 13/04/19.
//

#ifndef RT_SPHEREOBJECT_HPP
#define RT_SPHEREOBJECT_HPP

#include <string>
#include "Config/config.hpp"
#include "Camera/Camera.hpp"
#include "Debug/Debug.hpp"

#ifdef _WIN32
    #include "gtx/norm.hpp"
#elif __APPLE__
    #include <glm/detail/type_vec.hpp>
    #include <glm/vec3.hpp>
#endif

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