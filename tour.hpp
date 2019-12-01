//
// Created by Hysteresis on 2019/3/8.
//

#ifndef ASSIGNMENT2_TOUR_HPP
#define ASSIGNMENT2_TOUR_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include "city.hpp"

class genetic;
class tour {
private:
    //use set to eliminate duplicate
    std::set<const city*> citySet;
    //store all cities in vector
    std::vector<const city*> cities;
    //total distance of this tour
    double distance;

public:
    //a random salar
    static constexpr int SCALAR = 5894;
    //the mutation rate of tour is 15%
    static constexpr int MUTATION_RATE = 15;

    //not allowing default constructor
    tour() = delete;
    //tour can be init by a vector of city
    explicit tour(std::vector<const city*> cities);
    //default destructor
    ~tour() = default;
    //find if city is already in current tour using set
    bool contain(const city* c) const;
    //add city to this tour
    void add(const city* cur);
    //mutate current tour by looping through the tour
    // and swap this city with next city in this tour at 15% chance
    void mutate();
    //calculate the total distance of this tour
    void calcDistance();
    //calculate the fitness using scalar
    double getFitness();
    //print current tour to a string
    std::string print();

    //getters and setters
    const std::vector<const city *> &getCities() const;
    void setCities(const std::vector<const city *> &cities);
    const std::set<const city *> &getCitySet() const;
    void setCitySet(const std::set<const city *> &citySet);
    double getDistance() ;
    void setDistance(double distance);
};


#endif //ASSIGNMENT2_TOUR_HPP
