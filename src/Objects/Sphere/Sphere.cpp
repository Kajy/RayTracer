//
// Created by xw on 13/04/19.
//

#include <Common/Intersection.hpp>
#ifdef __APPLE__
#include <glm/detail/type_vec.hpp>
#endif
#include "Sphere.hpp"


Sphere::Sphere(): Sphere(0.0, 0.0, 0.0, 10, Color(255, 255, 255, 255))
{
}

Sphere::Sphere(double posX, double posY, double posZ, double radius, Color color):
	AHitable(Color(255, 255, 255, 0), glm::dvec3(posX, posY, posZ)),
	_radius(radius)
{
    _color = color;
}

Intersection		Sphere::hit(const glm::dvec3 &view, const glm::dvec3 &vecDir) const {

	double          a, b, c, d, k1, k2;
    Intersection    hit;

	a = (vecDir.x * vecDir.x) + (vecDir.y * vecDir.y) + (vecDir.z * vecDir.z);
	b = 2 * (((view.x - _position.x) * vecDir.x) + ((view.y - _position.y) * vecDir.y) + ((view.z - _position.z) * vecDir.z));
	c = ((view.x - _position.x) * (view.x - _position.x)) + ((view.y - _position.y) * (view.y - _position.y)) + ((view.z - _position.z) * (view.z - _position.z)) - (_radius * _radius);
	d = (b * b) - (4 * a * c);

	k1 = (-b + sqrt(d)) / (2 * a);
	k2 = (-b - sqrt(d)) / (2 * a);


	if (k1 > 0 || k2 > 0) {
		double finalDist = (k1 < k2 ? (k1 < 0 ? k2 : k1) : (k2 < 0 ? k1 : k2));
#if  DEBUG
		Debug::printInfo(std::string("Sphere: Collision Distance [" + std::to_string(finalDist) + "]").c_str());
#endif //  DEBUG
		hit.distanceWithViewer = finalDist;
		hit.hitPosition = view + vecDir * finalDist;
		hit.color = _color;
		hit.isHit = true;
	}
	return (hit);
}

glm::dvec3          Sphere::calcNormal(glm::dvec3 hitPoint) const {
    return glm::normalize(glm::dvec3(hitPoint - _position));
}

double Sphere::getRadius() const {
    return _radius;
}

void Sphere::setRadius(double radius) {
    _radius = radius;
}
