//
// Created by kj on 05/05/19.
//

#ifndef RT_TRIANGLE_HPP
#define RT_TRIANGLE_HPP

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

class Triangle : public AHitable
{
public:
	Triangle(glm::dvec3 const &A, glm::dvec3 const &B, glm::dvec3 const &C);
	~Triangle() = default;

	Intersection		    hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const override;
	glm::dvec3				calcNormal(glm::dvec3 const &) const override;
private:
	glm::dvec3		_A, _B, _C;

};

#endif //RT_TRIANGLE_HPP