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

void Airport::assertLength(std::string s, int i){
    if(s.length() == i){
        throw std::invalid_argument(
            std::string("Must be ") + std::to_string(i) + " characters long"
        );
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
    assertLength(continent, 2);
    this->continent = continent;
}

void Airport::setCountry(std::string country){
    assertNoBackslash(country);
    assertLength(country, 2);
    this->country = country;
}

void Airport::setRegion(std::string region){
    assertNoBackslash(country);
    this->region = region;
}

void Airport::setMunicipality(std::string name){
    assertNoBackslash(municipality);
    this->municipality = municipality;
}

void Airport::setICAOCode(std::string ICAOCode){
    assertNoBackslash(ICAOCode);
    assertLength(ICAOCode, 4);
    this->ICAOCode = ICAOCode;
}

void Airport::setIATACode(std::string IATACode){
    assertNoBackslash(IATACode);
    assertLength(IATACode, 3);
    this->IATACode = IATACode;
}

void Airport::setGPSCode(std::string GPSCode){
    assertNoBackslash(GPSCode);
    assertLength(GPSCode, 4);
    this->GPSCode = GPSCode;
}

void Airport::setLocalCode(std::string localCode){
    assertNoBackslash(localCode);
    this->localCode = localCode;
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