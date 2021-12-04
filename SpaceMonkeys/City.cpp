#include <iostream>
#include "City.h"

City::City(int population){
    // https://www.eia.gov/tools/faqs/faq.php?id=97 for energy consuption
    energyConsumptionRequired = 900 * population; // (in KWH per month)

}

void City::addWindMill(){
    // some constant More research here
    energyGenerated += 1000;
    enviornmentEffect += 0;

}

void City::addCoalPlant(){
    // some constant More research here
    energyGenerated += 1000;
    // some constant effect on enviornment
    enviornmentEffect += 100;
    
}

void City::addCattleFarm(){
    
}

void City::addAppartmentHousing(){
    
}

void City::addSubrubanHousing(){
    
}

void City::addAmusement(){
    
}