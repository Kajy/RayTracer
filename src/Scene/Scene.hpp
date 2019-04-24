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

#include "Config/config.hpp"
#include "Common/Intersection.hpp"
#include "Objects/AHitable.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Objects/Sphere/Sphere.hpp"
#include "Ray/Ray.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	Intersection	        renderScene(double x, double y, uint32_t maxWidth, uint32_t maxHeight);

	Camera const                        &getView() const;
    std::vector<AHitable *> const       &getHitableObjects() const;
    double                              getFarestDistanceHited() const;

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

private:

    double          _farestDistanceHited;

};

#endif //RT_SCENE_HPP
