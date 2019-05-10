//
// Created by xw on 13/04/19.
//

#include "Camera.hpp"

Camera::Camera(glm::dvec3 const &position, glm::dvec3 const &lookAt, glm::dvec3 const &upVector, glm::dvec2 const &screenSize, float fov) :
    AObject(position),
    _screenSize(screenSize)
{
    std::cout << "Screen Size [" << _screenSize.x << ", " << _screenSize.y << "]" << std::endl;
    _n = glm::normalize(position - lookAt);
    std::cout << "N Vector (" << _n.x << ", " << _n.y << ", " << _n.z << ")" << std::endl;
    _u = glm::cross(upVector, _n);
    std::cout << "U Vector (" << _u.x << ", " << _u.y << ", " << _u.z << ")" << std::endl;
    _v = glm::cross(_n, _u);
    std::cout << "V Vector (" << _v.x << ", " << _v.y << ", " << _v.z << ")" << std::endl;

    _distanceWithScreen = screenSize.y / (glm::tan(glm::radians(fov / 2)) * 2);
    std::cout << "Distance Eye / Screen : " << _distanceWithScreen << std::endl;
    _center = position - _n * _distanceWithScreen;
    _L = _center - _u * (screenSize.x / 2.0) - _v * (screenSize.y / 2.0);

    std::cout << "Center Position (" << _center.x << ", " << _center.y << ", " << _center.z << ")" << std::endl;
    std::cout << "L Position (" << _L.x << ", " << _L.y << ", " << _L.z << ")" << std::endl;

}

Camera::Camera(const glm::dvec3 &position) :
    Camera(position, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), glm::dvec2(WINDOW_W, WINDOW_H), FOV)
{

}

glm::dvec3      Camera::screenToWorldPos(double x, double y) {
    if (x ==0 && y ==0)
        std::cout << "L Position (" << _L.x << ", " << _L.y << ", " << _L.z << ")" << std::endl;
    return _L + _u * x * (_screenSize.x / WINDOW_W) + _v * y * (_screenSize.y / WINDOW_H);
}