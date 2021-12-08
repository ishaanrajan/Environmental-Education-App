#include <iostream>
#include <string>
#include <vector>

#include "City.h"

City::City(int population){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = 5 * population; // (in MWH per month)
    // environmental effect is in gCO2

}

City::City(int population, std::vector<std::string> prevBuilds){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = 5 * population; // (in MWH per month)

    // loop and add appropriate values
    for(std::string build : prevBuilds)
    {
        if(build == "WindMill")
        {
            addWindMill();
        } 
        else if(build == "CoalPlant")
        {
            addCoalPlant();
        }
        else if(build == "SolarFarm")
        {
            addSolarFarm();
        }
        else if(build == "Nuclear")
        {
            addNuclear();
        }

    }

}

void City::addWindMill(){
    // from diagram in megaWatt hours
    energyGenerated += 6800 * 30;
    environmentEffect += 0;

    allBuilds.push_back("WindMill");

}

void City::addCoalPlant(){
    // this is an average based on research
    energyGenerated += 50000 * 30;
    // some constant effect on enviornment
    environmentEffect += 1500;

    allBuilds.push_back("CoalPlant");
    
}

void City::addSolarFarm(){
    // some constant More research he all in MWH
    energyGenerated += 7200 * 30;
    // some constant effect on enviornment
    environmentEffect += 0;

    allBuilds.push_back("SolarFarm");
    
}

void City::addNuclear(){
    // some constant More research he all in MWH
    energyGenerated += 7200 * 30;
    // some constant effect on enviornment
    environmentEffect += 0;

    allBuilds.push_back("Nuclear");
    
}

void City::addCattleFarm(){
    // some constant penalties and additions
    energyGenerated -= 100;
    produceGenerated += 1000;
    environmentEffect -= 500;

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

void City::addDriveIn(){
    funGenerated += 100;
    allBuilds.push_back("DriveIn");
}

void City::addStadium(){
    funGenerated += 10000;
    // look at exact value
    energyGenerated -= 100;
    
    allBuilds.push_back("DriveIn");
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
