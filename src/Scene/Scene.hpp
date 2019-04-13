//
// Created by xw on 13/04/19.
//

#ifndef RT_SCENE_HPP
#define RT_SCENE_HPP

#include "gtx/norm.hpp"

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
