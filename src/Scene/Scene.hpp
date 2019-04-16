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

#include "Config/config.hpp"
#include "Camera/Camera.hpp"
#include "SphereObject/SphereObject.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	bool	renderScene(double x, double y);

private:
	Camera	_view;

	SphereObject	_sphereTest; //To remove just a test

};

#endif //RT_SCENE_HPP
