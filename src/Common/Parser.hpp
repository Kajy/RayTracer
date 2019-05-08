//
// Created by Julian Vives on 2019-04-19.
//

#ifndef RT_PARSER_HPP
#define RT_PARSER_HPP

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <Objects/Sphere/Sphere.hpp>
#include <Objects/PointLight/PointLight.hpp>
#include <Objects/Plane/Plane.hpp>
#include <Objects/Polygon/Polygon.hpp>
#include <sys/param.h>
#include <unistd.h>
#include <regex>
#include <sstream>
#include "Utils.hpp"

using namespace nlohmann;

class Parser {
private:
    enum OBJ_VALUES_TOKENS {
        OBJ_BEGIN_TOKEN = 'v',
        VERTICES_TOKEN = ' ',
        TEXTURES_TOKEN = 't',
        NORMAL_TOKEN = 'n'
    };
    enum LINK_VALUES_TOKENS {
        LINK_BEGIN_TOKEN = 'f',
        SEPARATOR_TOKEN = '/'
    };
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
            colorJson["blue"],
            colorJson["green"],
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

    static Plane        *ParsePlane(const json &j) {
        Plane           *plane = ParseHitableObject<Plane>(j);
        plane->setHeight(j["height"]);

        return plane;
    }

    static std::vector<Triangle *>      ParseObj(const json &j) {
        std::string     filename(j["path"]);
        std::ifstream   file(getWorkingPath() + "/scenes/" + filename);
        std::vector<glm::dvec3> valuesVertices;
        std::vector<glm::dvec3> valuesTextures;
        std::vector<glm::dvec3> valuesNormal;
        std::vector<Triangle *> triangles;

        std::string::size_type sz;     // alias of size_t

        if (file.is_open()) {
            std::string line;
            int token = 0, currentLine = 1, currentColumn = 0;
            while (file.good()) {
                char peek = file.get();
                ++currentColumn;
                if (peek == '\n' || peek == '\0') {
                    ++currentLine;
                    currentColumn = 0;
                }
                if (peek == OBJ_VALUES_TOKENS ::OBJ_BEGIN_TOKEN && currentColumn == 1) {
                    char nextToken = file.get();
                    switch (nextToken) {
                        case OBJ_VALUES_TOKENS::VERTICES_TOKEN: {
                            auto vertice = parseValues(file, 3, currentLine, currentColumn, filename);
                            valuesVertices.push_back(vertice);
                            break;
                        }
                        case OBJ_VALUES_TOKENS::TEXTURES_TOKEN: {
                            auto textures = parseValues(file, 2, currentLine, currentColumn, filename);
                            valuesTextures.push_back(textures);
                            break;
                        }
                        case OBJ_VALUES_TOKENS::NORMAL_TOKEN: {
                            auto normales = parseValues(file, 3, currentLine, currentColumn, filename);
                            valuesNormal.push_back(normales);
                            break;
                        }
                        default: {
                            std::stringstream iss;

                            iss << "Parse Error : File [" << filename << "] line : " << currentLine << " column : " << currentColumn << std::endl;
                            iss << "Reason : Invalid token '" << nextToken << "'" << std::endl;
                            std::cout << iss.str() << std::endl;
                            throw std::logic_error(iss.str());
                        }
                    }
                } else if (peek == LINK_VALUES_TOKENS::LINK_BEGIN_TOKEN && currentColumn == 1) {
                    std::string nb;
                    std::vector<std::tuple<glm::dvec3, glm::dvec3, glm::dvec3>> mapping;
                    // 1 face = 1 triangle = 3 points
                    peek = file.get();
                    currentColumn++;
                    for (int i = 0; i < 3; i++) {
                        // v/vt/vn
                        glm::dvec3 vertex, texture, normal;
                        for (int i1 = 0; i1 < 3; i1++) {
                            int idx;
                            nb.clear();
                            while (peek != '/' && peek != '\n' && peek != '\0') {
                                if (i1 > 0 && peek == ' ')
                                    break;
                                if (peek >= '0' && peek <= '9')
                                    nb += peek;
                                peek = file.get();
                                ++currentColumn;
                            }
                            if (peek == '\n' || peek == '\0') {
                                ++currentLine;
                                currentColumn = 0;
                            }
                            if (!nb.empty()) {
                                idx = std::stoi(nb);
                                if (i1 == 0) {
                                    vertex = valuesVertices[idx - 1];
                                } else if (i1 == 1) {
                                    texture = valuesTextures[idx - 1];
                                } else {
                                    normal = valuesNormal[idx - 1];
                                }
                            }
                            if (peek != '\n' && peek != '\0') {
                                peek = file.get();
                                ++currentColumn;
                            }
                        }
                        mapping.emplace_back(vertex, texture, normal);
                    }
                    Triangle *triangle = ParseHitableObject<Triangle>(j);
                    triangle->setVertices(mapping[0], mapping[1], mapping[2]);
                    triangles.push_back(triangle);
                    /*std::cout << "TRIANGLE" << std::endl;
                    for (auto &triangle : mapping) {
                        glm::dvec3 v, vt, vn;
                        std::tie(v, vt, vn) = triangle;
                        std::cout << "======================================================" << std::endl;
                        std::cout << "VERTEX " << v.x << " " << v.y << " " << v.z << std::endl;
                        std::cout << "TEXTURE " << vt.x << " " << vt.y << std::endl;
                        std::cout << "NORMAL " << vn.x << " " << vn.y << " " << vn.z << std::endl;
                    }
                    std::cout << std::endl;*/

                }
            }
            std::cout << std::endl;
        }
        file.close();
        return triangles;
    }

private:
    static std::string getWorkingPath()
    {
        char temp[MAXPATHLEN];
        return ( getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string("") );
    }

    static glm::dvec3  parseValues(std::ifstream &file, int nbValuesToParse, int &currentLine, int &currentColumn, const std::string &filename)
    {
        double        valuesConverted[3] = {0, 0, 0};
        std::string   nb;
        char          peek;

        for (int i = 0; i < nbValuesToParse; i++){
            nb.clear();
            while ((peek = file.get()) != '-' && !(peek >= '0' && peek <= '9')) {
                currentColumn++;
                if (peek == '\n' || peek == '\0') {
                    ++currentLine;
                    currentColumn = 0;
                }
            }
            nb += peek;
            while ((peek = file.get()) != ' ' && peek != '\0' && peek != '\n') {
                nb += peek;
                currentColumn++;
            }
            if (peek == '\n' || peek == '\0') {
                ++currentLine;
                currentColumn = 0;
            }
            try {
                valuesConverted[i] = std::stod(nb);
            } catch (const std::invalid_argument &e) {
                std::stringstream iss;

                iss << "Parse Error : File [" << filename << "] line : " << currentLine << " column : " << currentColumn << std::endl;
                iss << "Reason : Invalid number '" << nb << "'" << std::endl;
                std::cout << iss.str() << std::endl;
                throw std::logic_error(iss.str());
            }
        }

        return glm::dvec3(valuesConverted[0], valuesConverted[1], valuesConverted[2]);
    }
};
#endif //RT_PARSER_HPP
