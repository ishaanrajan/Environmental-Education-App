#include <iostream>
#include <string>
#include <vector>

#include "City.h"

City::City(){
    population = 1000000;
    energyConsumptionRequired = (5 * population) / 100;
    // on average 2 people per house
    housingRequired = (population/2)/1000;
    produceRequired = 100;
    funRequired = 100;
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
        if(build == "windfarm")
        {
            addWindFarm();
        } 
        else if(build == "factory1" || build == "factory2")
        {
            addCoalPlant();
        }
        else if(build == "solar")
        {
            addSolar();
        }
        else if(build == "nuclear")
        {
            addNuclear();
        }

    }

}

void City::environmentTracker(int enviroUpdate){
    if(environmentEffect + enviroUpdate > 99){
        environmentEffect = 100;
    }else{
        environmentEffect += enviroUpdate;
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

void City::housingTracker(int housingUpdate){
    if(housingUpdate + housingGenerated > housingRequired){
        housingRequired = housingRequired;
    }else{
        housingGenerated += housingUpdate;
    }
}

void City::foodTracker(int foodUpdate){
    if(foodUpdate + produceGenerated > produceRequired){
        produceRequired = produceRequired;
    }else{
        produceGenerated += foodUpdate;
    }
}


void City::funTracker(int funUpdate){
    if(funUpdate + amenitiesGenerated > funRequired){
        funRequired = funRequired;
    }else{
        amenitiesGenerated += funUpdate;
    }
}

void City::addWindFarm(){
    // from diagram in megaWatt hours
    // Times 30 days
    int energyUpdate = (7200 * 30)/100;
    energyTracker(energyUpdate);
    int enviroUpdate = 1;
    environmentTracker(enviroUpdate);
    allBuilds.push_back("windfarm");
}

void City::addCoalPlant(){
    // this is an average based on research
    int energyUpdate = (50000 * 30)/100;

    energyTracker(energyUpdate);
    // some constant effect on enviornment
    int enviroUpdate = 22;
    environmentTracker(enviroUpdate);

    allBuilds.push_back("factory1"); // TODO: difference between factor1 and factor2?
    
}

void City::addSolar(){
    // some constant More research he all in MWH
    int energyUpdate = (7200 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);
    int enviroUpdate = 5;
    environmentTracker(enviroUpdate);
    allBuilds.push_back("solar");
    
}

void City::addNuclear(){
    // some constant More research he all in MWH
     int energyUpdate = (95000 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);
    int enviroUpdate = 1;
    environmentTracker(enviroUpdate);

    allBuilds.push_back("nuclear");
    
}

void City::addCowFactory(){
    // some constant penalties and additions
    energyGenerated -= 10;
    int produceGen = 60;
    int enviroUpdate = 10;
    int funGenerate = 10;
    environmentTracker(enviroUpdate);
    foodTracker(produceGen);
    funTracker(funGenerate);

    allBuilds.push_back("CattleFarm");
}

void City::addPlantFarm(){
    // some constant penalties and additions
    energyGenerated -= 10;
    int produceGen = 30;
    int enviroUpdate = 10;
    environmentTracker(enviroUpdate);
    foodTracker(produceGen);
    allBuilds.push_back("PlantFarm");
}

void City::addHighDensityHousing(){
    int enviroUpdate = 8;
    environmentTracker(enviroUpdate);
    int housingGen = 100;
    housingTracker(housingGen);
    allBuilds.push_back("highdensityapartments");
}

void City::addSuburbanHousing(){
    int enviroUpdate = 15;
    environmentTracker(enviroUpdate);
    int housingGen = 60;
    housingTracker(housingGen);
    allBuilds.push_back("neighborhood");
}

void City::addTheater(){
    int funGen = 50;
    int enviroUpdate = 5;
    environmentTracker(enviroUpdate);
    funTracker(funGen);
    allBuilds.push_back("theater");
}

void City::addDriveIn(){
    int funGen = 100;
    int enviroUpdate = 7;
    environmentTracker(enviroUpdate);
    funTracker(funGen);
    allBuilds.push_back("drivein");
}

void City::addStadium(){
    int funGen = 10;
    energyGenerated -= 10;
    funTracker(funGen);
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

int City::getAmenitiesGenerated(){
    return amenitiesGenerated;
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


int City::getFunNeeded(){
    return funRequired;
}

int City::getFoodNeeded(){
    return produceRequired;
}

int City::getHousingNeeded(){
    return housingRequired;
}
