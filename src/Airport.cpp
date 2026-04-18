#include "include/Airport.h"
#include <stdexcept>
#include <iostream>

//Constructor(s)
Airport::Airport(){};


//Private Methods
void Airport::assertNoBackslash(std::string s){
    if(s.find("\\") != std::string::npos){
        throw std::invalid_argument("Cannot contain backslashes");
    }
}


//Setters
void Airport::setAirportType(AirportType type){
    this->type = type;
}

void Airport::setName(std::string name){
    assertNoBackslash(name);
    this->name = name;
}

void Airport::setElevation(short elevation){
    this->elevation = elevation;
}

void Airport::setContinent(std::string continent){
    assertNoBackslash(continent);
    if(continent.length() == 2){
        this->continent = continent;
    }else{
        throw std::invalid_argument("Continent code must be 2 characters long");
    }
}

void Airport::setCountry(std::string country){
    assertNoBackslash(country);
    if(country.length() == 2){
        this->country = country;
    }else{
        throw std::invalid_argument("Country code must be 2 characters long");
    }
}

void Airport::setRegion(std::string region){
    assertNoBackslash(country);
    this->region = region;
}

void Airport::setMunicipality(std::string name){
    assertNoBackslash(municipality);
    this->municipality = municipality;
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