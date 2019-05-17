//
// Created by xw on 13/04/19.
//

#ifndef RT_CAMERA_HPP
#define RT_CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../AObject.hpp"
#include "Common/Debug.hpp"
#include "Config/Configuration.hpp"
#ifdef _WIN32
    #include "glm/vec3.hpp"
#elif __APPLE__ or __linux__
    #include <glm/vec3.hpp>
#endif

class Camera : public AObject {
public:
	Camera() : Camera(glm::dvec3(-10.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), Resolution {1280, 720}, Resolution {1280, 720}, FOV) {};
	Camera(glm::dvec3 const &position, const Resolution &screenSize, const Resolution &drawableSurface, double fov);
	Camera(glm::dvec3 const &position, glm::dvec3 const &lookAt, glm::dvec3 const &upVector, const Resolution &screenSize, const Resolution &drawableSurface,double fov);
	Camera(glm::dvec3 const &position, glm::dvec3 const &lookAt, glm::dvec3 const &upVector);
	Camera(const glm::dvec3 &position);
	~Camera() = default;

	glm::dvec3      screenToWorldPos(double x, double y);

private:
    glm::dvec3      _n, _u, _v;
    Resolution      _screenSize;
    Resolution      _drawableSurface;
public:
    void setDrawableSurface(const Resolution &drawableSurface);

public:
    void setScreenSize(const Resolution &screenSize);

private:
    double          _distanceWithScreen;
    glm::dvec3      _center, _L;
};

#endif //RT_CAMERA_HPP