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
#ifdef _WIN32
#include <direct.h>
#elif __APPLE__ or __linux__
#include <sys/param.h>
#include <unistd.h>
#endif
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
    struct VertRef
    {
        VertRef( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
        int v, vt, vn;
    };

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


    static std::vector<Triangle *>      ParseObj(const json &json) {

        std::string     filename(json.at("path").get<std::string>());
        std::ifstream   file(getWorkingPath() + "/scenes/" + filename);
        std::vector<glm::dvec4> valuesVertices;
        std::vector<glm::dvec3> valuesTextures;
        std::vector<glm::dvec3> valuesNormal;
        std::vector<Triangle *> triangles;

        std::string::size_type sz;     // alias of size_t

        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {

                std::istringstream lineSS( line );
                std::string lineType;
                lineSS >> lineType;

                // vertex
                if( lineType == "v" )
                {
                    double x = 0, y = 0, z = 0, w = 1;
                    lineSS >> x >> y >> z >> w;
                    valuesVertices.emplace_back(glm::vec4( x, y, z, w ) );
                }

                // texture
                if( lineType == "vt" )
                {
                    double u = 0, v = 0, w = 0;
                    lineSS >> u >> v >> w;
                    valuesTextures.emplace_back(glm::vec3( u, v, w ) );
                }

                // normal
                if( lineType == "vn" )
                {
                    double i = 0, k = 0, l = 0;
                    lineSS >> i >> k >> l;
                    valuesNormal.emplace_back(glm::normalize( glm::vec3( i, k, l ) ) );
                }

                // polygon
                if( lineType == "f" )
                {
                    std::vector< VertRef > refs;
                    std::string refStr;
                    while( lineSS >> refStr )
                    {
                        std::istringstream ref( refStr );
                        std::string vStr, vtStr, vnStr;
                        std::getline( ref, vStr, '/' );
                        std::getline( ref, vtStr, '/' );
                        std::getline( ref, vnStr, '/' );

                        int v = vStr.empty() ? 0 : atoi( vStr.c_str() ) - 1;
                        int vt = vtStr.empty() ? 0 : atoi( vtStr.c_str() ) - 1;
                        int vn = vnStr.empty() ? 0 : atoi( vnStr.c_str() ) - 1;

                        v  = (  v >= 0 ?  v : valuesVertices.size() +  v );
                        vt = ( vt >= 0 ? vt : valuesTextures.size() + vt );
                        vn = ( vn >= 0 ? vn : valuesNormal.size()   + vn );
                        refs.emplace_back( v, vt, vn );
                    }

                    // triangulate, assuming n>3-gons are convex and coplanar
                    for( size_t i = 1; i+1 < refs.size(); ++i )
                    {
                        const VertRef* p[3] = { &refs[0], &refs[i], &refs[i+1] };

                        // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
                        glm::dvec3 U( valuesVertices[ p[1]->v ] - valuesVertices[ p[0]->v ] );
                        glm::dvec3 V( valuesVertices[ p[2]->v ] - valuesVertices[ p[0]->v ] );
                        glm::dvec3 faceNormal = glm::normalize( glm::cross( U, V ) );

                        std::vector<std::tuple<glm::dvec3, glm::dvec3, glm::dvec3>> mapping;
                        for( size_t j = 0; j < 3; ++j )
                        {
                            mapping.emplace_back(
                                    p[j]->v >= valuesVertices.size() ? glm::dvec3(0, 0, 0) : glm::dvec3( valuesVertices[ p[j]->v ] ),
                                    p[j]->vt >= valuesTextures.size() ? glm::dvec3(0, 0, 0) : glm::dvec3(valuesTextures[ p[j]->vt ]),
                                    p[j]->vn != 0 ? valuesNormal[ p[j]->vn ] : faceNormal);
                        }
                        Triangle *triangle = ParseHitableObject<Triangle>(json);
                        triangle->setVertices(mapping[0], mapping[1], mapping[2]);

                        triangles.emplace_back(triangle);

#if _DEBUG
                        for (auto &vert : mapping) {
                            glm::dvec3 v, vt, vn;
                            std::tie(v, vt, vn) = vert;
                            std::cout << "======================================================" << std::endl;
                            std::cout << "VERTEX " << v.x << " " << v.y << " " << v.z << std::endl;
                            std::cout << "TEXTURE " << vt.x << " " << vt.y << std::endl;
                            std::cout << "NORMAL " << vn.x << " " << vn.y << " " << vn.z << std::endl;
                        }
#endif
                    }
                }
            }
        }
		/*if (file.is_open()) {
			std::string line;
			int token = 0, currentLine = 1, currentColumn = 0;
			while (file.good()) {
				char peek = file.get();
				++currentColumn;
				if (peek == '\n' || peek == '\0') {
					++currentLine;
					currentColumn = 0;
				}
				if (peek == OBJ_VALUES_TOKENS::OBJ_BEGIN_TOKEN && currentColumn == 1) {
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
				}
				else if (peek == LINK_VALUES_TOKENS::LINK_BEGIN_TOKEN && currentColumn == 1) {
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
								}
								else if (i1 == 1) {
									texture = valuesTextures[idx - 1];
								}
								else {
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
					*//*std::cout << "TRIANGLE" << std::endl;
					for (auto &triangle : mapping) {
						glm::dvec3 v, vt, vn;
						std::tie(v, vt, vn) = triangle;
						std::cout << "======================================================" << std::endl;
						std::cout << "VERTEX " << v.x << " " << v.y << " " << v.z << std::endl;
						std::cout << "TEXTURE " << vt.x << " " << vt.y << std::endl;
						std::cout << "NORMAL " << vn.x << " " << vn.y << " " << vn.z << std::endl;
					}
					std::cout << std::endl;*//*

				}
			}
			std::cout << std::endl;
            file.close();
        }*/
		else
			std::cout << "Error obj file : " << (getWorkingPath() + "/scenes/" + filename) << std::endl;
        return triangles;
    }

private:
    static std::string getWorkingPath()
    {
#ifdef _WIN32
        char temp[255];
        return (_getcwd(temp, sizeof(temp)) ? std::string( temp ) : std::string("") );
#else
		char temp[MAXPATHLEN];
		return (getcwd(temp, sizeof(temp)) ? std::string(temp) : std::string(""));
#endif
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
