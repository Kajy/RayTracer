//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(-15.0, 0, 0),
	_farestDistanceHited(0)
{
	//_lights.push_back(new PointLight(-15.0, 5.0, -5.0));
}

Scene::~Scene()
{
    _hitableObjects.clear();
}

Intersection		    Scene::renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight) {

    Intersection intersection;
    glm::dvec3	_posView = _view.getPosition();

	Ray ray(_posView, glm::normalize(glm::dvec3(FOV - _posView.x, (maxWidth / 2.0) - x - _posView.y, (maxHeight / 2.0) - y - _posView.z)));

	// RENDER PIPELINE

	// --- SIMPLE HIT
    intersection = ray.launchRay(this->_hitableObjects);

    // --- LIGHTS EFFECTS
    if (intersection.isHit)
        intersection = renderLightsEffect(intersection);

	if (intersection.distanceWithViewer < MAX_DISTANCE) // Used to calculate distanceMap
	    _farestDistanceHited = glm::max(_farestDistanceHited, intersection.distanceWithViewer);


	return intersection;
}

Intersection            Scene::renderLightsEffect(Intersection const &inter) {

    Intersection    inLight(inter);
	double			dotAvg = 0;

    for (auto const &it: _lights) {
        glm::dvec3  dir(glm::normalize(it->getPosition() - inter.hitPosition));
		dotAvg += glm::dot(inLight.normal, dir);
    }

	inLight.color = inLight.color * (dotAvg / _lights.size());

    return inLight;
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
