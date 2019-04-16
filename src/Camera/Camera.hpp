//
// Created by xw on 13/04/19.
//

#ifndef RT_CAMERA_HPP
#define RT_CAMERA_HPP

#ifdef _WIN32
    #include "vec3.hpp"
#elif __APPLE__ or __linux__
    #include <glm/detail/type_vec.hpp>
    #include <glm/vec3.hpp>
#endif

class Camera
{
public:
	Camera();
	Camera(double x, double y, double z);
	~Camera();

	glm::dvec3 const &getPosition() const;

private:
	glm::dvec3	_pos;
};

#endif //RT_CAMERA_HPP