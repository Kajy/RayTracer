//
// Created by Julian Vives on 2019-04-15.
//

#ifndef RT_AOBJECT_HPP
#define RT_AOBJECT_HPP

#ifdef _WIN32
    #include "glm/gtx/norm.hpp"
#elif __APPLE__ or __linux__
    #include <glm/vec3.hpp>
#endif
/**
 * Base class for every object.
 */
class AObject {
private:
    AObject() = default;
protected:
    AObject(const glm::dvec3 &position) : _position(position) {};
public:
    void            setPosition(const glm::dvec3 &position) {
        _position = position;
    };

    const glm::dvec3       &getPosition() const {
        return _position;
    };
protected:
    glm::dvec3       _position;
};

#endif //RT_AOBJECT_HPP
