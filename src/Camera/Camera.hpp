//
// Created by xw on 13/04/19.
//

#ifndef RT_CAMERA_HPP
#define RT_CAMERA_HPP

#include "vec3.hpp"

class Camera
{
public:
	Camera();
	Camera(double x, double y, double z);
	~Camera();

	glm::dvec3 const &getPosition() const;

private:
	glm::dvec3	_pos;
};

#endif //RT_CAMERA_HPP