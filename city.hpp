//
// Created by Hysteresis on 2019/3/8.
//

#ifndef ASSIGNMENT2_CITY_HPP
#define ASSIGNMENT2_CITY_HPP

#include <iostream>
#include <cmath>

class city {
private:
    //name of the city
    std::string name;
    //x coord of the city
    double x;
    //y coord of the city
    double y;

public:
    //not allowing default constructor
    city() = delete;
    //init a city by name, and x y coords
    city(std::string& name, double x, double y);
    //copy constructor set to default
    city(const city& c) = default;
    //destructor set to default
    ~city() = default;
    //print this city to string
    std::string print() const;
    //calculate the distance of current city and given city
    static double getDistance(const city& a, const city& b);
    //overload = operator
    city& operator=(city c);
    //overload == operator
    bool operator==(const city& c);

    //getters and setters
    double getX() const;
    void setX(double x);
    double getY() const;
    void setY(double y);
    const std::string &getName() const;
    void setName(const std::string &name);
};


#endif //ASSIGNMENT2_CITY_HPP
