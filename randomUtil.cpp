//
// Created by Hysteresis on 2019/3/8.
//

#include <iostream>
#include "randomUtil.hpp"

const char randomUtil::alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int randomUtil::myrand_int(int a, int b){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

double randomUtil::myrand_double(double a, double b){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> distribution(a, b);
    return distribution(generator);
}

std::string randomUtil::myrand_string(int len) {
    std::string s;
    for (int i = 0; i < len; ++i) {
        s.push_back(static_cast<char>(myrand_int(33, 126)));
    }
    return s;
}