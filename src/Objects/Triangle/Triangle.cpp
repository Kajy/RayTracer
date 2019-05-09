//
// Created by kj on 05/05/19.
//

#include "Triangle.hpp"

Triangle::Triangle(glm::dvec3 const &A, glm::dvec3 const &B, glm::dvec3 const &C) :
	AHitable(Color(255, 255, 255, 0), glm::dvec3(0, 0, 0)),
	_A(A, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)),
	_B(B, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0)),
	_C(C, glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 0.0))
{
}


Intersection		Triangle::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {

	glm::dvec3 normale = calcNormal(view);
	Intersection	newInter;

	double t = glm::dot(std::get<0>(_C) - view, normale) / glm::dot(vecDir, normale);
	if (t < 0)
		return newInter;
	glm::dvec3 P = view + t * vecDir;

	glm::dvec3 u = std::get<0>(_B) - std::get<0>(_A);
	glm::dvec3 v = std::get<0>(_C) - std::get<0>(_A);
	glm::dvec3 w = P - std::get<0>(_A);

	double m11 = glm::length2(u);
	double m12 = glm::dot(u, v);
	double m22 = glm::length2(v);

	double deterM = (m11 * m22) - (m12 * m12);

	double b11 = glm::dot(w, u);
	double b21 = glm::dot(w, v);

	double deterB = b11 * m22 - b21 * m12;

	double b = deterB / deterM;

	double g12 = b11;
	double g22 = b21;
	double deterG = m11 * g22 - m12 * g12;

	double g = deterG / deterM;
	double a = 1 - b - g;

	if (a < 0 || b < 0 || g < 0 || a > 1 || b > 1 || g > 1)
		return newInter;

	newInter.isHit = true;
	newInter.color = _color;
	newInter.hitPosition = P;
	newInter.normal = normale;
	newInter.distanceWithViewer = t;

	return newInter;
}

glm::dvec3			Triangle::calcNormal(glm::dvec3 const &null) const {
	return glm::normalize(glm::cross(std::get<0>(_B) - std::get<0>(_A), std::get<0>(_C) - std::get<0>(_A)));
}

void                Triangle::setVertices(const std::tuple<glm::dvec3, glm::dvec3, glm::dvec3> &A,
                                          const std::tuple<glm::dvec3, glm::dvec3, glm::dvec3> &B,
                                          const std::tuple<glm::dvec3, glm::dvec3, glm::dvec3> &C) {
    _A = A;
    _B = B;
    _C = C;
}

Triangle::Triangle() : Triangle(glm::dvec3(0), glm::dvec3(0), glm::dvec3(0)) {
}
