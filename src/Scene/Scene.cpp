//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(-15.0, 0, 0),
	_farestDistanceHited(0)
{
}

Scene::~Scene()
{
    _hitableObjects.clear();
}

Intersection		    Scene::renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight) {

    glm::dvec3	_posView = _view.getPosition();

	Ray ray(_posView, glm::normalize(glm::dvec3(FOV - _posView.x, (maxWidth / 2.0) - x - _posView.y, (maxHeight / 2.0) - y - _posView.z)));

	Intersection newInter = ray.launchRay(this->_hitableObjects);

	if (newInter.distanceWithViewer < MAX_DISTANCE)
	    _farestDistanceHited = glm::max(_farestDistanceHited, newInter.distanceWithViewer);

	return newInter;
}

Camera const    &Scene::getView() const {
    return _view;
}

std::vector<AHitable *> const &Scene::getHitableObjects() const {
    return _hitableObjects;
}

double          Scene::getFarestDistanceHited() const {
    return _farestDistanceHited;
}

void Scene::setView(const Camera &view) {
    _view = view;
}

void            Scene::setHitableObjects(const std::vector<AHitable *> &objects) {
    _hitableObjects = objects;
}

const std::vector<ALight *> &Scene::getLights() const {
    return _lights;
}

void Scene::setLights(const std::vector<ALight *> &lights) {
    _lights = lights;
}
