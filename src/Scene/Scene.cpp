//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(-20.0, 0, 0)
{
    _shapeObjects.push_back(new Sphere());
}

Scene::~Scene()
{
}

bool		    Scene::renderScene(double x, double y) {

    glm::dvec3	_posView = _view.getPosition();

	//glm::dvec3	_vecDir(FOV - _posView.x, (WINDOW_W / 2.0) - x - _posView.y, (WINDOW_H / 2.0) - y - _posView.z);
	//_vecDir = glm::normalize(_vecDir);

	Ray ray(_posView, glm::normalize(glm::dvec3(FOV - _posView.x, (WINDOW_W / 2.0) - x - _posView.y, (WINDOW_H / 2.0) - y - _posView.z)));

	return (ray.launchRay(this->_shapeObjects));

}

Camera const    &Scene::getView() const {
    return _view;
}

std::vector<AShapeObject *> const &Scene::getShapeObjects() const {
    return _shapeObjects;
}