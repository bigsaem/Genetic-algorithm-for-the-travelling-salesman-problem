//
// Created by Hysteresis on 2019/3/8.
//

#ifndef ASSIGNMENT2_RANDOMUTIL_HPP
#define ASSIGNMENT2_RANDOMUTIL_HPP

#include <random>

class randomUtil {
private:
    //hidden constructor for static class
    randomUtil() = default;
public:
    //range of random char
    static const char alphanum[];
    //not allow copy
    randomUtil(const randomUtil& r) = delete;
    //not allow copy
    void operator=(const randomUtil& r) = delete;
    //get a random integer
    static int myrand_int(int a, int b);
    //get a random double
    static double myrand_double(double a, double b);
    //get a random string by given length
    static std::string myrand_string(int len);
};

#endif //ASSIGNMENT2_RANDOMUTIL_HPP
