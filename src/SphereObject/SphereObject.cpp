//
// Created by xw on 13/04/19.
//

#include <cmath>
#include "SphereObject.hpp"


SphereObject::SphereObject():
	_pos(0.0, 0.0, 0.0),
	_radius(10)
{
}

SphereObject::SphereObject(double posX, double posY, double posZ, double radius):
	_pos(posX, posY, posZ),
	_radius(radius)
{

}

SphereObject::~SphereObject()
{
}


double		SphereObject::isCollinding(glm::dvec3 view, glm::dvec3 vecDir) const {

	double a, b, c, d, k1, k2;

	a = (vecDir.x * vecDir.x) + (vecDir.y * vecDir.y) + (vecDir.z * vecDir.z);
	b = 2 * (((view.x - _pos.x) * vecDir.x) + ((view.y - _pos.y) * vecDir.y) + ((view.z - _pos.z) * vecDir.z));
	c = ((view.x - _pos.x) * (view.x - _pos.x)) + ((view.y - _pos.y) * (view.y - _pos.y)) + ((view.z - _pos.z) * (view.z - _pos.z)) - (_radius * _radius);
	d = (b * b) - (4 * a * c);

	k1 = (-b + sqrt(d)) / (2 * a);
	k2 = (-b - sqrt(d)) / (2 * a);


	if (k1 > 0 || k2 > 0) {
		double finalDist = (k1 < k2 ? (k1 < 0 ? k2 : k1) : (k2 < 0 ? k1 : k2));
#if  DEBUG
		Debug::printInfo(std::string("Sphere: Collision Distance [" + std::to_string(finalDist) + "]").c_str());
#endif //  DEBUG
		return finalDist;
	}
	return (-1);
}