//
// Created by Hysteresis on 2019/3/8.
//

#include "city.hpp"

city::city(std::string& name, double x, double y) : name(name), x(x), y(y){}

double city::getX() const {
    return x;
}

void city::setX(double x) {
    city::x = x;
}

double city::getY() const {
    return y;
}

void city::setY(double y) {
    city::y = y;
}

const std::string &city::getName() const {
    return name;
}

void city::setName(const std::string &name) {
    city::name = name;
}

std::string city::print() const {
    return "name: " + name
        + " x: " + std::to_string(x)
        + " y: " + std::to_string(y);
}

double city::getDistance(const city &a, const city &b) {
    return std::sqrt(std::pow(std::abs(a.x - b.x), 2) + std::pow(std::abs(a.y - b.y), 2));
}

city& city::operator=(city c) {
    std::swap(name, c.name);
    std::swap(x, c.x);
    std::swap(y, c.y);
    return *this;
}

bool city::operator==(const city &c) {
    return name == c.name && x == c.x && y == c.y;
}
