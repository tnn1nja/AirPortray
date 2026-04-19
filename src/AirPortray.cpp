#include "include/AirPortray.h"
#include <iostream>
#include <iomanip>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

void AirPortray::run(){
    cout << "AirPortray running!\n";
    displayAirports(repository->getSomeAirports());
    repository->saveIfDirty();
}

string AirPortray::truncateString(string s, unsigned int i){
    if(s.length() > i){
        s.erase(i-3);
        s = s + "...";
    }
    return s;
}

void AirPortray::displayAirports(list<Airport*> airports){
    cout << left << fixed
         << setw(14) << "Type" << " | "
         << setw(32) << "Name" << " | "
         << "Elevation (ft) | "
         << "Continent | "
         << "Country | " 
         << "Region | " 
         << setw(20) << "Municipality" << " | "
         << "ICAO Code | "
         << "IATA Code | " 
         << "GPS Code | " 
         << "Local Code | " 
         << "Coordinates"
         << endl;

    cout << setw(14) << Airport::typeToString(Airport::Type::MEDIUM_AIRPORT) << " | "
         << setw(32) << truncateString("Kitchen Creek Helibase Heliport With too long name", 32) << " | "
         << setw(14) << "32000" << " | "
         << setw(9) << "NA" << " | "
         << setw(7) << "US" << " | "
         << setw(6) << "US-PAU" << " | "
         << setw(20) << truncateString("Altamonte Springsfieldshoreship", 20) << " | "
         << setw(9) << "AAAA" << " | "
         << setw(9) << "BBB" << " | "
         << setw(8) << "CCCC" << " | "
         << setw(10) << "DDDD" << " | "
         << setprecision(3) << -123.456789 << ", "
         << setprecision(3) << -123.456789
         << endl;
    
    /*
    for(Airport* a: airports){
        cout << Airport::typeToString(a->getType()) << " | " << a->getName() << " | " << a->getElevation()
            << "ft | " << a->getContinent() << " | " << a->getRegion() << " | " << a->getMunicipality()
            << " | " << a->getICAOCode() << " | " << a->getIATACode() << " | " << a->getGPSCode()
            << " | " << a->getLocalCode() << " | " << a->getLatitude() << " | " << a->getLongitude() << endl;
    }
    */
}