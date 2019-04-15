//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(-20.0, 0, 0)
{
}

Scene::~Scene()
{
}

bool		Scene::renderScene(double x, double y) {

	glm::dvec3	_posView = _view.getPosition();

	glm::dvec3	_vecDir(FOV - _posView.x, (WINDOW_W / 2) - x - _posView.y, (WINDOW_H / 2) - y - _posView.z);
	_vecDir = glm::normalize(_vecDir);

	return (this->_sphereTest.calcCollision(_posView, _vecDir) > 0);

}