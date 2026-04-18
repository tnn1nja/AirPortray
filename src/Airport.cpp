#include "include/Airport.h"
#include <stdexcept>
#include <iostream>

//Constructor(s)
Airport::Airport(){};

//Setters
void Airport::setAirportType(AirportType type){
    this->type = type;
}
void Airport::setName(std::string name){
    if(name.find("\\") == std::string::npos){
        this->name = name;
    }else{
        std::cout << "Exception\n";
        //throw std::invalid_argument("Cannot contain backslashes");
    }
}

//Getters
AirportType Airport::getAirportType(){ return type; }
std::string Airport::getName(){ return name; }
short Airport::getElevation(){return elevation; }
std::string Airport::getContinent(){ return continent; }
std::string Airport::getCountry(){ return country; }
std::string Airport::getRegion(){ return region; }
std::string Airport::getMunicipality(){ return municipality; }
std::string Airport::getICAOCode(){ return ICAOCode; }
std::string Airport::getIATACode(){ return IATACode; }
std::string Airport::getGPSCode(){ return GPSCode; }
std::string Airport::getLocalCode(){ return localCode; }
double* Airport::getCoordinates(){ return coordinates; }