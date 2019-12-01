#include <utility>

//
// Created by Hysteresis on 2019/3/8.
//

#include "tour.hpp"
#include "randomUtil.hpp"


tour::tour(std::vector<const city*> cities) : citySet{cities.begin(), cities.end()}, cities{std::move(cities)} {}

bool tour::contain(const city *c) const {
    return citySet.find(c) != citySet.end();
}

void tour::add(const city *cur) {
    cities.push_back(cur);
    citySet.insert(cur);
}

void tour::mutate(){
    for(auto i = 0u; i < cities.size() - 1; ++i){
        int ran = randomUtil::myrand_int(0, 99);
        if(ran < MUTATION_RATE){
            auto iNext = (i + 1u) % cities.size();
            std::swap(cities[i], cities[iNext]);
        }
    }
}

std::string tour::print(){
    std::string res = "distance: " + std::to_string(distance) + "\nroute: \n";
    int i = 0;
    for(auto cPtr : cities){
        res += cPtr->print();
        res += "\n";
        ++i;
    }
    return res;
}

const std::vector<const city *> &tour::getCities() const {
    return cities;
}

void tour::setCities(const std::vector<const city *> &cities) {
    tour::cities = cities;
}

const std::set<const city *> &tour::getCitySet() const {
    return citySet;
}

void tour::setCitySet(const std::set<const city *> &citySet) {
    tour::citySet = citySet;
}

double tour::getDistance() {
    calcDistance();
    return distance;
}

void tour::setDistance(double distance) {
    tour::distance = distance;
}

double tour::getFitness() {
    return 1 / getDistance() * SCALAR;
}

void tour::calcDistance() {
    if(cities.size() < 2){
        return;
    }
    distance = 0;
    for(int i = 0; i < cities.size() - 1; ++i){
        distance += city::getDistance(*cities[i], *cities[i + 1]);
    }
}
