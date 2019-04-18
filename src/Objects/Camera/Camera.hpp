//
// Created by xw on 13/04/19.
//

#ifndef RT_CAMERA_HPP
#define RT_CAMERA_HPP

#include "../AObject.hpp"
#ifdef _WIN32
    #include "glm/vec3.hpp"
#elif __APPLE__ or __linux__
    #include <glm/detail/type_vec.hpp>
    #include <glm/vec3.hpp>
#endif

class Camera : public AObject {
public:
	Camera() : Camera(0, 0, 0) {};
	Camera(double x, double y, double z);
	Camera(const glm::vec3 &position) : AObject(position) {};
	~Camera();

};

#endif //RT_CAMERA_HPP