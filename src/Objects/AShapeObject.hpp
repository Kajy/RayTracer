//
// Created by Julian Vives on 2019-04-15.
//

#ifndef RT_ASHAPEOBJECT_HPP
#define RT_ASHAPEOBJECT_HPP

#include <glm/gtx/norm.hpp>

#include "AObject.hpp"
#include "Common/Intersection.hpp"
#include "Common/Color.hpp"

class AShapeObject : public AObject {
private:
    AShapeObject() = default;

protected:
    AShapeObject(const Color &color, const glm::dvec3 &position) : AShapeObject(0, 0, color, position) {}

    AShapeObject(double shining, double refractionIndex, const Color &color, const glm::dvec3 &position) :
    AObject(position),
    _color(color),
    _shining(shining),
    _refractionIndex(refractionIndex) {};

protected:
    double  _shining;
    double  _refractionIndex;
    Color   _color;

public:
    double getShining() const {
        return _shining;
    }

    void setShining(double shining) {
        _shining = shining;
    }

    double getRefractionIndex() const {
        return _refractionIndex;
    }

    void setRefractionIndex(double refractionIndex) {
        _refractionIndex = refractionIndex;
    }

    const Color &getColor() const {
        return _color;
    }

    void setColor(const Color &color) {
        _color = color;
    }

    virtual Intersection    calcCollision(glm::dvec3 view, glm::dvec3 vecDir) const = 0;
    virtual glm::dvec3      calcNormal(glm::dvec3 hitPoint) const = 0;
};


#endif //RT_ASHAPEOBJECT_HPP
