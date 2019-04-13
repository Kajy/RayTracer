//
// Created by xw on 13/04/19.
//

#include "Camera.hpp"

Camera::Camera():
	_pos(0.0, 0.0, 0.0)
{
}

Camera::Camera(double x, double y, double z) :
	_pos(x, y, z)
{
}

Camera::~Camera()
{
}

glm::dvec3 const &Camera::getPosition() const
{
	return _pos;
}