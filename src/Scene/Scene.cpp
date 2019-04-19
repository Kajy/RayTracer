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
    _shapeObjects.push_back(new Sphere(0.0, -10.0, 0.0, 5, Color(255, 0, 0, 255)));
    _shapeObjects.push_back(new Sphere(0.0, 10.0, 0.0, 5, Color(0, 255, 0, 255)));

    _lights.push_back(new PointLight(-15.0, 5.0, -5.0));
}

Scene::~Scene()
{
}

Intersection		    Scene::renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight) {

    Intersection intersection;
    glm::dvec3	_posView = _view.getPosition();

	Ray ray(_posView, glm::normalize(glm::dvec3(FOV - _posView.x, (maxWidth / 2.0) - x - _posView.y, (maxHeight / 2.0) - y - _posView.z)));

	// RENDER PIPELINE

	// --- SIMPLE HIT
    intersection = ray.launchRay(this->_shapeObjects);

    // --- LIGHTS EFFECTS
    if (intersection.isHit)
        intersection = renderLightsEffect(intersection);

	if (intersection.distanceWithViewer < MAX_DISTANCE) // Used to calculate distanceMap
	    _farestDistanceHited = glm::max(_farestDistanceHited, intersection.distanceWithViewer);


	return intersection;
}

Intersection            Scene::renderLightsEffect(Intersection const &inter) {

    Intersection    inLight(inter);

    for (auto const &it: _lights) {
        glm::dvec3  dir(glm::normalize(it->getPosition() - inter.hitPosition));
        inLight.color = inLight.color * glm::dot(inLight.normal, dir);
    }

    return inLight;
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