#include <iostream>
#include <string>
#include <vector>

#include "City.h"

City::City(){
    population = 1000000;
    energyConsumptionRequired = (5 * population) / 100;
}
City::City(int population){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = (5 * population) / 100; // (in MWH per month)
    // environmental effect is in gCO2

}

City::City(int population, std::vector<std::string> prevBuilds){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = (5 * population)/ 100; // (in MWH per month)
    environmentEffect = 0;
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

void City::energyTracker(int energyUpdate){
    if(energyGenerated + energyUpdate > energyConsumptionRequired)
    {
            energyGenerated = energyConsumptionRequired;
    }else
    {
         energyGenerated += energyUpdate;
    }

}

void City::addWindMill(){
    // from diagram in megaWatt hours
    // Times 30 days
    int energyUpdate = (7200 * 30)/100;
    energyTracker(energyUpdate);

    environmentEffect += 0;

    allBuilds.push_back("WindMill");

}

void City::addCoalPlant(){
    // this is an average based on research
    int energyUpdate = (50000 * 30)/100;

    energyTracker(energyUpdate);
    // some constant effect on enviornment
    environmentEffect += 22;

    allBuilds.push_back("CoalPlant");
    
}

void City::addSolarFarm(){
    // some constant More research he all in MWH
    int energyUpdate = (7200 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);

    allBuilds.push_back("SolarFarm");
    
}

void City::addNuclear(){
    // some constant More research he all in MWH
     int energyUpdate = (95000 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);

    environmentEffect += 1;
    allBuilds.push_back("Nuclear");
    
}

void City::addCattleFarm(){
    // some constant penalties and additions
    energyGenerated -= 1;
    produceGenerated += 10;
    environmentEffect += 5;

    allBuilds.push_back("CattleFarm");
}

void City::addApartmentHousing(){
    environmentEffect += 1;

    allBuilds.push_back("Apartments");
}

void City::addSuburbanHousing(){
    environmentEffect += 10;

    allBuilds.push_back("Suburban");
}

void City::addDriveIn(){
    funGenerated += 100;
    allBuilds.push_back("DriveIn");
}

void City::addStadium(){
    funGenerated += 10;
    // look at exact value
    energyGenerated -= 10;
    
    allBuilds.push_back("Stadium");
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


int City::getEnergyNeeded(){
    return energyConsumptionRequired;
}
