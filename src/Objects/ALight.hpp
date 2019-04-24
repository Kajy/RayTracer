//
// Created by Julian Vives on 2019-04-21.
//

#ifndef RT_ALIGHT_HPP
#define RT_ALIGHT_HPP

#include "Common/Color.hpp"
#include "AObject.hpp"

class ALight : public AObject {
private:
    ALight() = default;

protected:
    ALight(const glm::dvec3 &position) : ALight(Color(255, 255, 255, 0), position) {};
    ALight(const Color &color, const glm::dvec3 &position) : ALight(color, position, 0) {};

    ALight(const Color &color, const glm::dvec3 &position, double intensity) :
    AObject(position),
    _color(color),
    _intensity(intensity) {}

    virtual ~ALight() = default;
protected:
    Color       _color;
public:
    const Color &getColor() const {
        return _color;
    }

    void setColor(const Color &color) {
        _color = color;
    }

    double getIntensity() const {
        return _intensity;
    }

    void setIntensity(double intensity) {
        _intensity = intensity;
    }

protected:
    double      _intensity;
};
#endif //RT_ALIGHT_HPP
