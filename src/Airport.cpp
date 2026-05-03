#include "include/Airport.h"
#include <stdexcept>
#include <cmath>

using namespace std;

//Static methods
string Airport::typeToString(Type type){
    string map[] = {
        "Balloonport",
        "Closed",
        "Heliport",
        "Large Airport",
        "Medium Airport",
        "Seaplane Base",
        "Small Airport",
        ""
    };
    return map[static_cast<int>(type)];
}

string Airport::typeToString(int type){
    return typeToString(static_cast<Airport::Type>(type));
}

//Private Methods
void Airport::assertNoBackslash(const string& s){
    if(s.find("\\") != string::npos){
        throw invalid_argument("cannot contain backslashes");
    }
}

void Airport::assertLength(const string& s, unsigned int i){
    if(s.length() != i && s.length() != 0){ //allow 0 length as null value
        throw invalid_argument(
            string("must be ") + to_string(i) + " characters long"
        );
    }
}

//Constructor
Airport::Airport(){
    type = Type::UNKNOWN;
    name = "";
    continent = "";
    country = "";
    region = "";
    municipality = "";
    ICAOCode = "";
    IATACode = "";
    GPSCode = "";
    localCode = "";
    elevation = SHRT_NULL;
    latitude = NAN;
    longitude = NAN;
}

//Setters
void Airport::setType(Type type){
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

void Airport::setMunicipality(string municipality){
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
Airport::Type Airport::getType(){ return type; }
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