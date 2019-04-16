//
// Created by Julian Vives on 2019-04-15.
//

#ifndef RT_COLOR_HPP
#define RT_COLOR_HPP

typedef struct Color {
   char      red;
   char      green;
   char      blue;
   char      alpha;
   Color(char r, char g, char b, char a) : red(r), blue(b), green(g), alpha(a) {}
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
