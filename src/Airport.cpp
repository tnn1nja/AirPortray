#include "include/Airport.h"
#include <stdexcept>
#include <iostream>
#include <climits>
#include <cmath>

using namespace std;

//Constructor
Airport::Airport(){
    type = AirportType::UNKNOWN;
    name = "";
    continent = "";
    country = "";
    region = "";
    municipality = "";
    ICAOCode = "";
    IATACode = "";
    GPSCode = "";
    localCode = "";
    elevation = SHRT_MIN; //using min as a null
    latitude = NAN;
    longitude = NAN;
}


//Private Methods
void Airport::assertNoBackslash(const string& s){
    if(s.find("\\") != string::npos){
        throw invalid_argument("Cannot contain backslashes");
    }
}

void Airport::assertLength(const string& s, unsigned int i){
    if(s.length() != i && s.length() != 0){ //allow 0 length as null value
        throw invalid_argument(
            string("Must be ") + to_string(i) + " characters long"
        );
    }
}


//Setters
void Airport::setType(AirportType type){
    this->type = type;
}

void Airport::setName(string name){
    assertNoBackslash(name);
    this->name = name;
}

void Airport::setElevation(short elevation){
    this->elevation = elevation;
}

void Airport::setContinent(string continent){
    assertNoBackslash(continent);
    assertLength(continent, 2);
    this->continent = continent;
}

void Airport::setCountry(string country){
    assertNoBackslash(country);
    assertLength(country, 2);
    this->country = country;
}

void Airport::setRegion(string region){
    assertNoBackslash(country);
    this->region = region;
}

void Airport::setMunicipality(string name){
    assertNoBackslash(municipality);
    this->municipality = municipality;
}

void Airport::setICAOCode(string ICAOCode){
    assertNoBackslash(ICAOCode);
    assertLength(ICAOCode, 4);
    this->ICAOCode = ICAOCode;
}

void Airport::setIATACode(string IATACode){
    assertNoBackslash(IATACode);
    assertLength(IATACode, 3);
    this->IATACode = IATACode;
}

void Airport::setGPSCode(string GPSCode){
    assertNoBackslash(GPSCode);
    this->GPSCode = GPSCode;
}

void Airport::setLocalCode(string localCode){
    assertNoBackslash(localCode);
    this->localCode = localCode;
}

void Airport::setLatitude(double latitude){
    this->latitude = latitude;
}

void Airport::setLongitude(double longitude){
    this->longitude = longitude;
}


//Getters
AirportType Airport::getType(){ return type; }
string Airport::getName(){ return name; }
short Airport::getElevation(){return elevation; }
string Airport::getContinent(){ return continent; }
string Airport::getCountry(){ return country; }
string Airport::getRegion(){ return region; }
string Airport::getMunicipality(){ return municipality; }
string Airport::getICAOCode(){ return ICAOCode; }
string Airport::getIATACode(){ return IATACode; }
string Airport::getGPSCode(){ return GPSCode; }
string Airport::getLocalCode(){ return localCode; }
double Airport::getLatitude(){ return latitude; }
double Airport::getLongitude(){ return longitude; }