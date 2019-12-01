//
// Created by Hysteresis on 2019/3/8.
//

#include "genetic.hpp"

genetic genetic::instance{};

std::vector<const city*> genetic::shuffle(std::vector<const city*> list){
    for(int i = 0; i < SHUFFLES; ++i){
        int ran1 = randomUtil::myrand_int(0, static_cast<int>(list.size() - 1));
        int ran2 = randomUtil::myrand_int(0, static_cast<int>(list.size() - 1));
        if(ran1 != ran2){
            std::swap(list[ran1], list[ran2]);
        }
    }
    return list;
}

void genetic::run(){
    using namespace std;

    createMasterList();
    createPopulation();
    moveEliteToFront();

    base_distance = best_distance = population[0]->getDistance();

    double baseFitness = population[0]->getFitness();
    double bestFitness = baseFitness;

    cout << "All generated tour are shown as follow:" << endl << endl;
    for(auto t : population){
        cout << t->print() << endl;
    }
    cout <<  "Base distance of genetic algorithm is: "<< base_distance << endl << endl;

    cout <<  "Genetic algorithm starts, process will terminate when improvement factor reach: "<< IMPROVEMENT_FACTOR << endl << endl;
    int iteration = 0;

    while(bestFitness / baseFitness < 1 + IMPROVEMENT_FACTOR && iteration < ITERATIONS){
        auto children = batchCrossover();
        for(auto iter = population.begin() + NUMBER_OF_ELITES; iter != population.end(); ++iter){
            delete *iter;
            *iter = nullptr;
        }
        std::copy(children.begin(), children.end(), population.begin() + NUMBER_OF_ELITES);
        moveEliteToFront();
        best_distance = population[0]->getDistance();
        bestFitness = population[0]->getFitness();
        mutate();

        cout << "Iteration " << iteration << endl;
        cout << "Best distance in this iteration is:"<< best_distance << endl;
        cout << "Improvement of this iteration compared to base is:" << bestFitness / baseFitness - 1 << endl << endl;
        ++iteration;
    }

    cout << "Genetic algorithm terminated, the final best tour is: " << endl << endl;
    cout << population[0]->print() << endl;

}

void genetic::createMasterList(){
    for(int i = 0; i < CITY_IN_TOUR; ++i){
        std::string name = "city " + std::to_string(i);
        auto c = new city{name, randomUtil::myrand_double(0, MAP_BOUNDARY), randomUtil::myrand_double(0, MAP_BOUNDARY)};
        masterList.push_back(c);
    }
}

genetic* genetic::getInstance() {
    return &instance;
}

void genetic::createPopulation() {
    for(int i = 0; i < POPULATION_SIZE; ++i){
        auto shuffledList = shuffle(masterList);
        tour* t = new tour{shuffledList};
        population.push_back(t);
    }
}

genetic::~genetic() {
    for(auto v : masterList){
        delete v;
    }
    for(auto v : population){
        delete v;
    }
}

void genetic::moveEliteToFront() {
    for(int i = 0; i < NUMBER_OF_ELITES; ++i){
        int fitIndex = i;
        for(int j = i + 1; j < POPULATION_SIZE; ++j){
            if(population[j]->getFitness() > population[fitIndex]->getFitness()){
                fitIndex = j;
            }
        }
        if(i != fitIndex){
            std::swap(population[i], population[fitIndex]);
        }
    }
}

std::vector<tour*> genetic::selectParents() {
    std::vector<tour*> parents{};
    for(int parentCount = 0; parentCount < POPULATION_SIZE / 3; ++parentCount){
        std::vector<tour*> backup{population.begin(), population.end()};
        tour* fittestParentInPool = nullptr;
        for(int parentPoolSize = 0; parentPoolSize < PARENT_POOL_SIZE; ++parentPoolSize){
            int rani = randomUtil::myrand_int(0, static_cast<int>(backup.size() - 1));
            if(fittestParentInPool == nullptr || backup[rani]->getFitness() > fittestParentInPool->getFitness()){
                fittestParentInPool = backup[rani];
            }
            backup.erase(backup.begin() + rani);
        }
        parents.push_back(fittestParentInPool);
    }
    return parents;
}

void genetic::mutate() {
    for(int i = NUMBER_OF_ELITES; i < POPULATION_SIZE; ++i){
        population[i]->mutate();
    }
}

std::vector<tour *> genetic::batchCrossover() {
    std::vector<tour *> child;
    for(int i = 0; i < POPULATION_SIZE - NUMBER_OF_ELITES; ++i){
        auto parentList = selectParents();
        std::set<tour *> parents{};
        for(int j = 0; j < NUMBER_OF_PARENTS;){
            int rani = randomUtil::myrand_int(0, static_cast<int>(parentList.size()) - 1);
            if(parents.find(parentList[rani]) == parents.end()){
                parents.insert(parentList[rani]);
                ++j;
            }
        }
        std::vector<tour *> reducer{parents.begin(), parents.end()};
        auto nChild = crossover(reducer);
        child.push_back(nChild);
    }
    return child;
}

tour *genetic::crossover(std::vector<tour *> parents) {
    auto totalParent = parents.size();
    int lastRan = randomUtil::myrand_int(0, static_cast<int>(parents[0]->getCities().size() - totalParent));
    tour t{std::vector<const city*>{parents[0]->getCities().begin(), parents[0]->getCities().begin() + lastRan + 1}};
    for(auto parentCount = 1u; parentCount < totalParent - 1; ++parentCount){
        int thisRan = randomUtil::myrand_int(lastRan + 1, static_cast<int>(parents[parentCount]->getCities().size() - totalParent + parentCount));
        for(int i = lastRan + 1, j = 0; i <= thisRan; ++i){
            const city* c;
            do{
                c = parents[parentCount]->getCities()[j];
                ++j;
            } while (t.contain(c));
            t.add(c);
        }
        lastRan = thisRan;
    }
    for(int i = lastRan + 1, j = 0; i < CITY_IN_TOUR; ++i){
        const city* c;
        do{
            c = parents[totalParent - 1]->getCities()[j];
            ++j;
        } while (t.contain(c));
        t.add(c);
    }
    return new tour{t};
}


