//
// Created by Julian Vives on 2019-04-15.
//

#ifndef RT_COLOR_HPP
#define RT_COLOR_HPP

typedef struct Color {
   unsigned char      red;
   unsigned char      green;
   unsigned char      blue;
   unsigned char      alpha;
   Color(): red(0), blue(0), green(0), alpha(0) {}
   Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : red(r), blue(b), green(g), alpha(a) {}
   Color(const Color &copy) : red(copy.red), blue(copy.blue), green(copy.green), alpha(copy.alpha) {}
   Color &operator=(const Color &copy) {
       red = copy.red;
       blue = copy.blue;
       green = copy.green;
       alpha = copy.alpha;
       return *this;
   }
} Color;

#endif //RT_COLOR_HPP
