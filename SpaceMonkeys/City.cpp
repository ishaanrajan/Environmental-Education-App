#include <iostream>
#include <string>
#include <vector>

#include "City.h"

City::City(int population){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = 900 * population; // (in KWH per month)

}

City::City(int population, std::vector<std::string> prevBuilds){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = 900 * population; // (in KWH per month)

    // add a stich statement
    // for(std::string build : prevBuilds)
    // {

    // }

}

void City::addWindMill(){
    // some constant More research here
    energyGenerated += 1000;
    environmentEffect += 0;

    allBuilds.push_back("WindMill");

}

void City::addCoalPlant(){
    // some constant More research here
    energyGenerated += 1000;
    // some constant effect on enviornment
    environmentEffect += 100;

    allBuilds.push_back("CoalPlant");
    
}

void City::addCattleFarm(){
    // some constant penalties and additions
    energyGenerated -= 10;
    produceGenerated += 1000;
    environmentEffect -= 100;

    allBuilds.push_back("CattleFarm");
}

void City::addApartmentHousing(){
    environmentEffect += 100;

    allBuilds.push_back("Apartments");
}

void City::addSuburbanHousing(){
    environmentEffect -= 100;

    allBuilds.push_back("Suburban");
}

void City::addAmusement(){
    funGenerated += 1000;
    allBuilds.push_back("Amusement");
}

// getters for all values in the game.

std::vector<std::string> City::getAllBuilds(){
    return allBuilds;
}

int City::getEnergyGenerated(){
    return energyGenerated;
}

int City::getEnvironmentEffect(){
    return environmentEffect;
}

int City::getFunGenerated(){
    return funGenerated;
}

int City::getHousingGenerated(){
    return housingGenerated;
}

int City::getProduceGenerated(){
    return produceGenerated;
} 