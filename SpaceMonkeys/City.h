#ifndef CITY_H
#define CITY_H

#include <iostream>
#include <string>
#include <vector>


/*
This is the City class.
*/
class City {
public:
    /*
    This is the constructor for the City class.
    */
    City(int pop);

   /*
    This is the constructor for the City class for new rounds.
    */
    City(int population, std::vector<std::string> prevBuilds);

    /**
     * @brief This method is used when the user decides
     * to add a windMill.
     *
     */
    void addWindMill();

    /**
     * @brief This method is used when the user decides
     * to add a coalPlant.
     *
     */
    void addCoalPlant();

    /**
     * @brief This method is used when the user decides
     * to add a cattleFarm.
     *
     */
    void addCattleFarm();

    /**
     * @brief This method is used when the user decides
     * to add housing.
     *
     */
    void addApartmentHousing();

    /**
     * @brief This method is used when the user decides
     * to add housing.
     *
     */
    void addSuburbanHousing();

    /**
     * @brief This method is used when the user decides
     * to add a windMill.
     *
     */
    void addAmusement();


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
     * @brief This method is used to return fun generated
     *
     */
    int getFunGenerated();

     /**
     * @brief This method is used to return fun generated
     *
     */
    int getProduceGenerated();

    /**
     * @brief This method is used to return fun generated
     *
     */
    int getHousingGenerated();

    /**
     * @brief Meant for the end of the round to save progress.
     *
     */
    std::vector<std::string> getAllBuilds();



private:
    int population;

    std::vector<std::string> allBuilds;

    // Default calculated values
    int energyConsumptionRequired;
    int produceRequired;
    int housingRequired;

    // Dynamic
    int environmentEffect;
    int energyGenerated;
    int funGenerated;
    int produceGenerated;
    int housingGenerated;
};

#endif
