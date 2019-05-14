//
// Created by xw on 13/04/19.
//

#include "Camera.hpp"

Camera::Camera(glm::dvec3 const &position, glm::dvec3 const &lookAt, glm::dvec3 const &upVector, const Resolution &screenSize, const Resolution &drawableSurface, double fov) :
    AObject(position),
    _screenSize(screenSize),
    _drawableSurface(drawableSurface)
{
    _n = glm::normalize(position - lookAt);
    _u = glm::cross(upVector, _n);
    _v = glm::cross(_n, _u);

    _distanceWithScreen = screenSize.height / (glm::tan(glm::radians(fov / 2)) * 2);
    _center = position - _n * _distanceWithScreen;
    _L = _center - _u * (screenSize.width / 2.0) - _v * (screenSize.height / 2.0);

}

Camera::Camera(const glm::dvec3 &position) :
    Camera(position, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), Resolution {1280, 720}, Resolution {1280, 720}, 30.0)
{

}

glm::dvec3      Camera::screenToWorldPos(double x, double y) {
    return _L + _u * x * (_drawableSurface.width / _screenSize.width) + _v * y * (_drawableSurface.height / _screenSize.height);
}

void Camera::setScreenSize(const Resolution &screenSize) {
    _screenSize = screenSize;
}

void Camera::setDrawableSurface(const Resolution &drawableSurface) {
    _drawableSurface = drawableSurface;
}
