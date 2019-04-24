//
// Created by xw on 13/04/19.
//

#ifndef RT_SPHERE_HPP
#define RT_SPHERE_HPP

#include <string>
#include <cmath>
#include "Config/config.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Common/Debug.hpp"
#include <Objects/AHitable.hpp>

#ifdef _WIN32
    #include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/vec3.hpp>
#endif

class Sphere : public AHitable
{
public:
	Sphere();
	Sphere(double posX, double posY, double posZ, double radius, Color color);
	~Sphere() = default;

	double		hit(glm::dvec3 view, glm::dvec3 vecDir) const override;
private:
	double		_radius;
public:
    double getRadius() const;

    void setRadius(double radius);

};

#endif //RT_SPHERE_HPP