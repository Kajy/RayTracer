//
// Created by xw on 12/04/19.
//

#ifndef RT_DEBUG_HPP
#define RT_DEBUG_HPP

#include <iostream>

class   Debug {

public:

    static void printSuccess(char const *msg) { std::cout << "[SUCCESS]\t" << msg << std::endl; }
    static void printInfo(char const *msg) { std::cout << "[INFO]\t\t" << msg << std::endl; }
    static void printError(char const *msg) { std::cout << "[ERROR]\t\t" << msg << std::endl; }


};

#endif //RT_DEBUG_HPP
