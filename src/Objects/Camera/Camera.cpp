//
// Created by xw on 13/04/19.
//

#include "Camera.hpp"

Camera::Camera(glm::dvec3 const &position, glm::dvec3 const &lookAt, glm::dvec3 const &upVector, glm::dvec2 const &screenSize, float fov) :
    AObject(position),
    _screenSize(screenSize)
{
    _n = glm::normalize(position - lookAt);
    _u = glm::cross(upVector, _n);
    _v = glm::cross(_n, _u);

    _distanceWithScreen = screenSize.y / (glm::tan(glm::radians(fov / 2)) * 2);
    _center = position - _n * _distanceWithScreen;
    _L = _center - _u * (screenSize.x / 2.0) - _v * (screenSize.y / 2.0);

}

Camera::Camera(const glm::dvec3 &position) :
    Camera(position, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), glm::dvec2(WINDOW_W, WINDOW_H), FOV)
{

}

glm::dvec3      Camera::screenToWorldPos(double x, double y) {
    return _L + _u * x * (_screenSize.x / WINDOW_W) + _v * y * (_screenSize.y / WINDOW_H);
}