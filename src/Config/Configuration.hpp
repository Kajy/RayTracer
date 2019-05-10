//
// Created by xw on 12/04/19.
//

#ifndef RT_CONFIGURATION_HPP
#define RT_CONFIGURATION_HPP

#define DEBUG false
#define WINDOW_W 1280
#define WINDOW_H 720
#define MAX_DISTANCE 999

#define	FOV	30.0

#define ANTI_ALIASING 1

typedef struct s_Resolution {
    double      width;
    double      height;
}               Resolution;

typedef struct s_Configuration {
    Resolution  resolution;
    int         maxDistance;
    double      fov;
    int         antiAliasing;
}               Configuration;

#define	BLACK_COLOR	0x00000000
#define WHITE_COLOR	0xFFFFFFFF

#endif //RT_CONFIGURATION_HPP
