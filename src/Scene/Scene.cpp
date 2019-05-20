//
// Created by xw on 13/04/19.
//

#include <iostream>

#include "Scene.hpp"


Scene::Scene():
	_view(glm::dvec3(-15.0, 0, 0), glm::dvec3(0.0, 0.0, 0.0), glm::dvec3(0.0, 0.0, 1.0), Resolution {1280.0, 720.0}, Resolution {1280.0, 720.0}, 30.0)
{
}

Scene::~Scene()
{
    _hitableObjects.clear();
}

Color		    Scene::renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight, uint32_t aa) {

    glm::dvec3  finalRGB;
    glm::dvec3	_posView = _view.getPosition();

    for (uint32_t aa_x = 0; aa_x < aa; ++aa_x) {
        for (uint32_t aa_y = 0; aa_y < aa; ++aa_y) {
            Ray ray(_posView, glm::normalize(_view.screenToWorldPos(x + static_cast<double>(aa_x) / aa, y + static_cast<double>(aa_y) / aa) - _posView));

            // RENDER PIPELINE

            // --- SIMPLE HIT
            Intersection intersection = ray.launchRay(this->_hitableObjects);

            if (intersection.isHit) {

                // --- LIGHTS EFFECTS
                intersection = renderLightsEffect(intersection);

                // --- SHADOW EFFECTS
                intersection = renderShadowsEffect(intersection);

                finalRGB.r += intersection.color.red;
                finalRGB.g += intersection.color.green;
                finalRGB.b += intersection.color.blue;
                //return intersection.color;
            }
        }
    }
    uint32_t powAa = aa * aa;
	return Color(static_cast<unsigned char>(finalRGB.r / (powAa)), static_cast<unsigned char>(finalRGB.g / (powAa)), static_cast<unsigned char>(finalRGB.b / (powAa)), 255);
}

Intersection            Scene::renderShadowsEffect(Intersection const &inter) {

    Intersection    inShadow(inter);
	uint32_t		shadowCount = _lights.size();

    for (auto const &it: _lights) {
        glm::dvec3 dirToLight = it->getPosition() - inter.hitPosition;
        Ray ray(inter.hitPosition + inter.normal * BIAS, glm::normalize(dirToLight));
        Intersection toLight = ray.launchRay(this->_hitableObjects);
        if (toLight.isHit)
            --shadowCount;
    }

	inShadow.color = inShadow.color * (shadowCount / static_cast<float>(_lights.size()));

    return inShadow;
}

Intersection            Scene::renderLightsEffect(Intersection const &inter) {

	Intersection    inLight(inter);
	double			dotAvg = 0;

	for (auto const &it : _lights) {
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

void Scene::setView(const Camera &view) {
    _view = view;
}

void            Scene::setHitableObjects(const std::vector<AHitable *> &objects) {
    _hitableObjects = objects;
}

void			Scene::setHitableObject(AHitable *object) {
	_hitableObjects.push_back(object);
}

const std::vector<ALight *> &Scene::getLights() const {
    return _lights;
}

void Scene::setLights(const std::vector<ALight *> &lights) {
    _lights = lights;
}
