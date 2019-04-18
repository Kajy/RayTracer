//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(-15.0, 0, 0),
	_farestDistanceHited(0)
{
    _shapeObjects.push_back(new Sphere(0.0, 0.0, 0.0, 10, Color(255, 255, 255, 255)));
  //  _shapeObjects.push_back(new Sphere(0.0, -20.0, 0.0, 5, Color(255, 0, 0, 255)));
   // _shapeObjects.push_back(new Sphere(0.0, 20.0, 0.0, 5, Color(0, 255, 0, 255)));
}

Scene::~Scene()
{
}

Intersection		    Scene::renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight) {

    glm::dvec3	_posView = _view.getPosition();

	Ray ray(_posView, glm::normalize(glm::dvec3(FOV - _posView.x, (maxWidth / 2.0) - x - _posView.y, (maxHeight / 2.0) - y - _posView.z)));

	Intersection newInter = ray.launchRay(this->_shapeObjects);

	if (newInter.distanceWithViewer < MAX_DISTANCE)
	    _farestDistanceHited = glm::max(_farestDistanceHited, newInter.distanceWithViewer);

	return newInter;
}

Camera const    &Scene::getView() const {
    return _view;
}

std::vector<AShapeObject *> const &Scene::getShapeObjects() const {
    return _shapeObjects;
}

double          Scene::getFarestDistanceHited() const {
    return _farestDistanceHited;
}