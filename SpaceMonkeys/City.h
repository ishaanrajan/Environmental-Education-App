#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <vector>


/*
This is the City class. 
*/
class City{

public:

    City();
    /*
    This is the constructor for the City class.
    */
    City(int pop);

   /*
    This is the constructor for the City class for new rounds.
    */
    City(int population, std::vector<std::string> prevBuilds);


    /**
     * @brief This method is used to add a plant farm
     * 
     */
    void addPlantFarm();

    /**
     * @brief This method is used when the user decides
     * to add a windMill.
     * 
     */
    void addWindFarm();

    /**
     * @brief This method is used when the user decides
     * to add a nuclearPlant.
     * 
     */
    void addNuclear();

    /**
     * @brief This method is used when the user decides
     * to add a coalPlant.
     * 
     */
    void addCoalPlant();

     /**
     * @brief This method is used when the user decides
     * to add a solarFarm.
     * 
     */
    void addSolar();

    /**
     * @brief This method is used when the user decides
     * to add a cattleFarm.
     * 
     */
    void addCowFactory();

    /**
     * @brief This method is used when the user decides
     * to add housing.
     * 
     */
    void addHighDensityHousing();

    /**
     * @brief This method is used when the user decides
     * to add housing.
     * 
     */
    void addSuburbanHousing();

    /**
     * @brief This method is used when the user decides
     * to add a theater.
     * 
     */
    void addTheater();

       /**
     * @brief This method is used when the user decides
     * to add a DriveIn.
     * 
     */
    void addDriveIn();

	
    /**
     * @brief This method is used when the user choses to add
     * a stadium
     * 
     */
    void addStadium();


    /**
     * @brief This method is used to return environment effect
     * 
     */
    int getEnvironmentEffect();

    /**
     * @brief This method is used to return energy generated
     * 
     */
    int getEnergyGenerated();

    /**
     * @brief This method is used to return amenities  generated
     * 
     */
    int getAmenitiesGenerated();

     /**
     * @brief This method is used to return food generated
     * 
     */
    int getFoodGenerated();

    /**
     * @brief This method is used to return housing generated
     * 
     */
    int getHousingGenerated();

    /**
     * @brief Meant for the end of the round to save progress.
     * 
     */
    std::vector<std::string> getAllBuilds();


    /**
     * @brief Get the energy that needs to be generated.
     * 
     */
    int getEnergyNeeded();

    /**
     * @brief Get the energy that needs to be generated.
     * 
     */
    int getFunNeeded();

       /**
     * @brief Get the energy that needs to be generated.
     * 
     */
    int getFoodNeeded();

    /**
     * @brief Get the energy that needs to be generated.
     * 
     */
    int getHousingNeeded();


private:
    std::vector<std::string> allBuilds;
    int population;

    void energyTracker(int energyUpdate);

    void environmentTracker(int enviroUpdate);

     /**
     * @brief Used to update the housing.
     * 
     */
    void housingTracker(int housingUpdate);

    void foodTracker(int housingUpdate);

    void funTracker(int housingUpdate);


    // Default calculated values
    int energyConsumptionRequired;
    int produceRequired;
    int housingRequired;
    int funRequired;

    // Dynamic 
    int environmentEffect = 0;
    int energyGenerated = 0;
    int amenitiesGenerated = 0;
    int produceGenerated = 0;
    int housingGenerated = 0;
};

#endif
