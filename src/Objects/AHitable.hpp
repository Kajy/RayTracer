//
// Created by Julian Vives on 2019-04-15.
//

#ifndef RT_AHITABLE_HPP
#define RT_AHITABLE_HPP

#include <glm/gtx/norm.hpp>

#include "AObject.hpp"
#include "Common/Intersection.hpp"
#include "Common/Color.hpp"

class AHitable : public AObject {
private:
    AHitable() = default;

protected:
    AHitable(const Color &color, const glm::dvec3 &position) : AHitable(0, 0, color, position) {}

    AHitable(double shining, double refractionIndex, const Color &color, const glm::dvec3 &position) :
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

    virtual glm::dvec3      calcNormal(glm::dvec3 hitPoint) const = 0;

    virtual Intersection hit(glm::dvec3 view, glm::dvec3 vecDir) const = 0;
    virtual ~AHitable() = default;

};


#endif //RT_AHITABLE_HPP