//
// Created by kj on 05/05/19.
//

#include "Triangle.hpp"

Triangle::Triangle(glm::dvec3 const &A, glm::dvec3 const &B, glm::dvec3 const &C) :
	AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)),
	_A(A, glm::dvec3(0.0, 0.0, 0.0), glm::dvec2(0.0, 0.0)),
	_B(B, glm::dvec3(0.0, 0.0, 0.0), glm::dvec2(0.0, 0.0)),
	_C(C, glm::dvec3(0.0, 0.0, 0.0), glm::dvec2(0.0, 0.0))
{
    _normal = glm::normalize(glm::cross(std::get<0>(_B) - std::get<0>(_A), std::get<0>(_C) - std::get<0>(_A)));
    _u = std::get<0>(_B) - std::get<0>(_A);
    _v = std::get<0>(_C) - std::get<0>(_A);

    _m11 = glm::length2(_u);
    _m12 = glm::dot(_u, _v);
    _m22 = glm::length2(_v);

    _deterM = (_m11 * _m22) - (_m12 * _m12);
}


Intersection		Triangle::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {

	Intersection	newInter;
	double t = glm::dot(std::get<0>(_C) - view, _normal) / glm::dot(vecDir, _normal);
	if (t < 0)
		return newInter;
	glm::dvec3 P = view + t * vecDir;

	glm::dvec3 w = P - std::get<0>(_A);


	double b11 = glm::dot(w, _u);
	double b21 = glm::dot(w, _v);

	double deterB = b11 * _m22 - b21 * _m12;

	double b = deterB / _deterM;

	double deterG = _m11 * b21 - _m12 * b11;

	double g = deterG / _deterM;
	double a = 1 - b - g;

	if (a < 0 || b < 0 || g < 0 || a > 1 || b > 1 || g > 1)
		return newInter;

	newInter.isHit = true;
	newInter.color = _color;
	newInter.hitPosition = P;
	newInter.normal = _normal;
	newInter.distanceWithViewer = t;

	return newInter;
}

glm::dvec3			Triangle::calcNormal(glm::dvec3 const &null) const {
	return glm::normalize(glm::cross(std::get<0>(_B) - std::get<0>(_A), std::get<0>(_C) - std::get<0>(_A)));
}

void                Triangle::setVertices(const std::tuple<glm::dvec3, glm::dvec3, glm::dvec2> &A,
                                          const std::tuple<glm::dvec3, glm::dvec3, glm::dvec2> &B,
                                          const std::tuple<glm::dvec3, glm::dvec3, glm::dvec2> &C) {
    _A = A;
    _B = B;
    _C = C;
    _normal = glm::normalize(glm::cross(std::get<0>(_B) - std::get<0>(_A), std::get<0>(_C) - std::get<0>(_A)));
    _u = std::get<0>(_B) - std::get<0>(_A);
    _v = std::get<0>(_C) - std::get<0>(_A);

    _m11 = glm::length2(_u);
    _m12 = glm::dot(_u, _v);
    _m22 = glm::length2(_v);

    _deterM = (_m11 * _m22) - (_m12 * _m12);
}

Triangle::Triangle() : Triangle(glm::dvec3(0), glm::dvec3(0), glm::dvec3(0)) {
}
