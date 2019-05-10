//
// Created by xw on 13/04/19.
//

#ifndef RT_SCENE_HPP
#define RT_SCENE_HPP

#ifdef _WIN32
    #include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/glm.hpp>
    #include <glm/vec3.hpp>
#endif

#include <vector>
#include <Objects/ALight.hpp>

#include "Config/Configuration.hpp"
#include "Common/Intersection.hpp"
#include "Objects/AHitable.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Objects/Sphere/Sphere.hpp"
#include "Objects/Triangle/Triangle.hpp"
#include "Objects/PointLight/PointLight.hpp"
#include "Ray/Ray.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	Color	                renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight);
	Intersection            renderLightsEffect(Intersection const &inter);
	Intersection            renderShadowsEffect(Intersection const &inter);

	Camera const                        &getView() const;
    std::vector<AHitable *> const       &getHitableObjects() const;

private:
	Camera	_view;
public:
    void setView(const Camera &view);

private:
    std::vector<AHitable *>             _hitableObjects;
    std::vector<ALight *>               _lights;
public:
    const std::vector<ALight *> &getLights() const;

    void setLights(const std::vector<ALight *> &lights);

public:
    void                                setHitableObjects(const std::vector<AHitable *> &shapeObjects);
	void								setHitableObject(AHitable *shapeObject);
};

#endif //RT_SCENE_HPP
