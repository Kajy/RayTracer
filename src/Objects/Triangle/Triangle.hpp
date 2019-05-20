//
// Created by kj on 05/05/19.
//

#ifndef RT_TRIANGLE_HPP
#define RT_TRIANGLE_HPP

#include <string>
#include <cmath>
#include <tuple>
#include "Config/Configuration.hpp"
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
    Triangle();
	Triangle(glm::dvec3 const &A, glm::dvec3 const &B, glm::dvec3 const &C);

    Triangle(const glm::dvec3 &A, const glm::dvec3 &B, const glm::dvec3 &C, const Color &color);

    Triangle(const glm::dvec3 &A, const glm::dvec3 &B, const glm::dvec3 &C, const Color &color, double refractionIndex,
                 double shining);

    ~Triangle() = default;

	Intersection		    hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const override;
	glm::dvec3				calcNormal(glm::dvec3 const &) const override;
	void                    setVertices(const std::tuple<glm::dvec3, glm::dvec2, glm::dvec3> &A,
                                        const std::tuple<glm::dvec3, glm::dvec2, glm::dvec3> &B,
                                        const std::tuple<glm::dvec3, glm::dvec2, glm::dvec3> &C);
private:

	std::tuple<glm::dvec3, glm::dvec2, glm::dvec3>	_A, _B, _C;
    glm::dvec3      _normal, _u, _v;

    double          _m11, _m12, _m22, _deterM;
};

#endif //RT_TRIANGLE_HPP