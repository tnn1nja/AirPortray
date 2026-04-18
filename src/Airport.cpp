#include "include/Airport.h"

Airport::Airport(){};

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