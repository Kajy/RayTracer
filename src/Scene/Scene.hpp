//
// Created by xw on 13/04/19.
//

#ifndef RT_SCENE_HPP
#define RT_SCENE_HPP

#ifdef _WIN32
    #include "gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/glm.hpp>
    #include <glm/detail/type_vec.hpp>
    #include <glm/vec3.hpp>
#endif

#include <vector>

#include "Config/config.hpp"
#include "Common/Intersection.hpp"
#include "Objects/AShapeObject.hpp"
#include "Objects/Camera/Camera.hpp"
#include "Objects/Sphere/Sphere.hpp"
#include "Ray/Ray.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	Intersection	        renderScene(double x, double y);

	Camera const                        &getView() const;
    std::vector<AShapeObject *> const   &getShapeObjects() const;

private:
	Camera	_view;

	std::vector<AShapeObject *>   _shapeObjects;
	Sphere	_sphereTest; //To remove just a test

};

#endif //RT_SCENE_HPP
