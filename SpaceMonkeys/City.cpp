#include <iostream>
#include <string>
#include <vector>

#include "City.h"

City::City()
{
    population = 100000;
    updatePopulation(1.0);
}

void City::updatePopulation(double factor)
{
    population = population * factor;
    energyConsumptionRequired = (5 * population) / 75;
    // on average 2 people per house
    housingRequired = (population/2)/1000;
    foodRequired = population/2000;
    amenitiesRequired = population/1000;
}

int City::numberDemandsSatisfied()
{
    int sumDemands = 0;
    if(energyGenerated >= energyConsumptionRequired)
        sumDemands += 1;
    if(housingGenerated >= housingRequired)
        sumDemands += 1;
    if(amenitiesGenerated >= amenitiesRequired)
        sumDemands += 1;
    if(foodGenerated >= foodRequired)
        sumDemands += 1;
    return sumDemands;
}

void City::environmentTracker(int enviroUpdate){
    environmentEffect += enviroUpdate;
//    if(environmentEffect + enviroUpdate > 100){
//        environmentEffect = 100;
//    }else{
//        environmentEffect += enviroUpdate;
//    }
}
void City::energyTracker(int energyUpdate){
    energyGenerated += energyUpdate;
//    if(energyGenerated + energyUpdate > energyConsumptionRequired)
//    {
//        energyGenerated = energyConsumptionRequired;
//    }else
//    {
//        energyGenerated += energyUpdate;
//    }
}

void City::housingTracker(int housingUpdate){
    housingGenerated += housingUpdate;
//    if(housingUpdate + housingGenerated >= housingRequired){
//        housingGenerated = housingRequired;
//    }else{
//        housingGenerated += housingUpdate;
//    }
}

void City::foodTracker(int foodUpdate){
    foodGenerated += foodUpdate;
//    if(foodUpdate + foodGenerated >= foodRequired){
//        foodGenerated = foodRequired;
//    }else{
//        foodGenerated += foodUpdate;
//    }
}


void City::amenitiesTracker(int amenityUpdate){
    amenitiesGenerated += amenityUpdate;
//    if(amenityUpdate + amenitiesGenerated >= amenitiesRequired){
//        amenitiesGenerated = amenitiesRequired;
//    }else{
//        amenitiesGenerated += amenityUpdate;
//    }
}

void City::addWindFarm(){
    // from diagram in megaWatt hours
    // Times 30 days
    int energyUpdate = (7200 * 30)/100;
    energyTracker(energyUpdate);
    int enviroUpdate = -5;
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

    allBuilds.push_back("coalplant");
    
}

void City::addSolar(){
    // some constant More research he all in MWH
    int energyUpdate = (7200 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);
    int enviroUpdate = -5;
    environmentTracker(enviroUpdate);
    allBuilds.push_back("solar");
    
}

void City::addNuclear(){
    // some constant More research he all in MWH
     int energyUpdate = (95000 * 30)/100;
    // some constant effect on enviornment
    energyTracker(energyUpdate);
    int enviroUpdate = 0;
    environmentTracker(enviroUpdate);

    allBuilds.push_back("nuclear");
    
}

void City::addCowFactory(){
    // some constant penalties and additions
    energyGenerated -= 10;
    int produceGen = 75;
    int enviroUpdate = 10;
    int funGenerate = 10;
    environmentTracker(enviroUpdate);
    foodTracker(produceGen);
    amenitiesTracker(funGenerate);

    allBuilds.push_back("cowfactory");
}

void City::addPlantFarm(){
    // some constant penalties and additions
    energyGenerated -= 10;
    int produceGen = 50;
    int enviroUpdate = -4;
    environmentTracker(enviroUpdate);
    foodTracker(produceGen);
    allBuilds.push_back("plantFarm");
}

void City::addHighDensityHousing(){
    int enviroUpdate = 8;
    environmentTracker(enviroUpdate);
    int housingGen = 60;
    housingTracker(housingGen);
    allBuilds.push_back("highdensityapartments");
}

void City::addSuburbanHousing(){
    int enviroUpdate = 15;
    environmentTracker(enviroUpdate);
    int housingGen = 50;
    housingTracker(housingGen);
    amenitiesTracker(15);
    allBuilds.push_back("neighborhood");
}

void City::addPark(){
    int funGen = 50;
    int enviroUpdate = -5;
    environmentTracker(enviroUpdate);
    amenitiesTracker(funGen);
    allBuilds.push_back("park");
}

void City::addDriveIn(){
    int funGen = 25;
    int enviroUpdate = 7;
    environmentTracker(enviroUpdate);
    amenitiesTracker(funGen);
    allBuilds.push_back("drivein");
}

void City::addStadium(){
    int funGen = 75;
    energyTracker(-10);
    int enviroUpdate = 15;
    environmentTracker(enviroUpdate); //TODO: clean these unnecessary lines
    amenitiesTracker(funGen);
    allBuilds.push_back("stadium");
}

void City::resetGeneratedValues(){
    amenitiesGenerated = 0;
    foodGenerated = 0;
    energyGenerated = 0;
    housingGenerated = 0;
    environmentEffect = 0;
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
    return foodGenerated;
}

int City::getEnergyNeeded(){
    return energyConsumptionRequired;
}


int City::getAmenitiesNeeded(){
    return amenitiesRequired;
}

int City::getFoodNeeded(){
    return foodRequired;
}

int City::getHousingNeeded(){
    return housingRequired;
}

int City::getDemandEnergyGenerated()
{
    return energyGenerated < energyConsumptionRequired ? energyGenerated : energyConsumptionRequired;
}

int City::getDemandAmenitiesGenerated()
{
    return amenitiesGenerated < amenitiesRequired ? amenitiesGenerated : amenitiesRequired;
}

int City::getDemandFoodGenerated()
{
    return foodGenerated < foodRequired ? foodGenerated : foodRequired;
}

int City::getDemandHousingGenerated()
{
    return housingGenerated < housingRequired ? housingGenerated : housingRequired;
}

int City::getDemandEnvironmentGenerated(){
    int enviroVal = environmentEffect > 100 ? 100 : environmentEffect;
    enviroVal = enviroVal < 0 ? 0 : enviroVal;
    return enviroVal;
}

int City::getPopulation()
{
    return population;
}
