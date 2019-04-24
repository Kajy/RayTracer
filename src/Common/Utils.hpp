//
// Created by Julian Vives on 2019-04-21.
//

#ifndef RT_UTILS_HPP
#define RT_UTILS_HPP

class Utils {
public:
    static constexpr unsigned int str2int(const char* str, int h = 0)
    {
        return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
    }
};
#endif //RT_UTILS_HPP
