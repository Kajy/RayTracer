//
// Created by Julian Vives on 2019-04-19.
//

#ifndef RT_PARSER_HPP
#define RT_PARSER_HPP

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <Objects/Sphere/Sphere.hpp>
#include <Objects/PointLight/PointLight.hpp>

using namespace nlohmann;

class Parser {
public:

    template<typename T>
    static T            *ParseHitableObject(const json &j) {
        T               *hitableObject = new T;

        hitableObject->setColor(ParseColor(j));
        hitableObject->setPosition(ParsePosition(j));
        hitableObject->setRefractionIndex(j["refractionIndex"]);
        hitableObject->setShining(j["shining"]);

        return hitableObject;
    }

    template <typename T>
    static T            *ParseLight(const json &j) {
        T               *light = new T(ParsePosition(j));

        light->setIntensity(j["intensity"]);
        light->setColor(ParseColor(j));

        return light;
    }

    static glm::dvec3   ParsePosition(const json &j) {
        const json &positionJson = j["position"];
        return glm::dvec3(positionJson["x"], positionJson["y"], positionJson["z"]);
    }

    static Color        ParseColor(const json &j) {
        const json &colorJson = j["color"];
        return Color {
            colorJson["red"],
            colorJson["green"],
            colorJson["blue"],
            colorJson["alpha"]
        };
    }

    static Sphere       *ParseSphere(const json &sphereJson) {
        Sphere          *sphere = ParseHitableObject<Sphere>(sphereJson);

        sphere->setRadius(sphereJson["radius"]);
        return sphere;
    }

    static Camera       ParseCamera(const json &j) {
        return Camera {ParsePosition(j)};
    }


};
#endif //RT_PARSER_HPP
