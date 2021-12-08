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
        if(build == "windarm")
        {
            addWindMill();
        } 
        else if(build == "factor1")
        {
            addCoalPlant();
        }
        else if(build == "solar")
        {
            addSolarFarm();
        }
        else if(build == "powerplant")
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

    allBuilds.push_back("windfarm");

}

void City::addCoalPlant(){
    // this is an average based on research
    int energyUpdate = (50000 * 30)/100;

    energyTracker(energyUpdate);
    // some constant effect on enviornment
    environmentEffect += 22;

    allBuilds.push_back("factory1"); // TODO: difference between factor1 and factor2?
    
}

void City::addSolarFarm(){
    // some constant More research he all in MWH
    int energyUpdate = (7200 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);

    allBuilds.push_back("solar");
    
}

void City::addNuclear(){
    // some constant More research he all in MWH
     int energyUpdate = (95000 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);
    environmentEffect += 1;
    allBuilds.push_back("powerplant");
    
}

void City::addCattleFarm(){
    // some constant penalties and additions
    // We don't have any farming categories what is this doing?? --Ishaan
    energyGenerated -= 1;
    produceGenerated += 10;
    environmentEffect += 5;

    allBuilds.push_back("CattleFarm");
}

void City::addApartmentHousing(){
    environmentEffect += 1;
    housingGenerated += 40;

    allBuilds.push_back("highdensityapartments");
}

void City::addSuburbanHousing(){
    environmentEffect += 10;
    housingGenerated += 20;

    allBuilds.push_back("neighborhood");
}

void City::addTheater(){
    funGenerated += 50;
    allBuilds.push_back("theater");
}

void City::addDriveIn(){
    funGenerated += 100;
    allBuilds.push_back("drivein");
}

void City::addStadium(){
    funGenerated += 10;
    // look at exact value
    // We don't have a stadium what is this doing?? --Ishaan
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

int City::getFoodGenerated(){
    return produceGenerated;
}


int City::getEnergyNeeded(){
    return energyConsumptionRequired;
}
