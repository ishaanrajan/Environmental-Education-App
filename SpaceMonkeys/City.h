#ifndef CITY_H
#define CITY_H

#include <iostream>

/*
This is the City class. 
*/
class City {
public:
    /*
    This is the constructor for the City class.
    */
    City(int pop);

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
    void addAppartmentHousing();

    /**
     * @brief This method is used when the user decides
     * to add housing.
     * 
     */
    void addSubrubanHousing();

    /**
     * @brief This method is used when the user decides
     * to add a windMill.
     * 
     */
    void addAmusement();





private:
    int population;

    // Default calculated values
    int energyConsumptionRequired;
    int produceRequired;
    int housingRequired;

    // Dynamic 
    int enviornmentEffect;
    int energyGenerated;
    int funGenerated;
    int produceGenerated;
};

#endif