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

void AirPortray::displayAirports(list<Airport*> airports){
    cout << left << fixed << "Type | " << "Name | " << "Elevation | " << "Continent | "
         << "ISO Country | " << "ISO Region | " << "Municipality | " << "ICAO Code | "
         << "IATA Code | " << "GPS Code | " << "Local Code | " << "Latitude | " << "Longitude | "
         << endl;

    cout << Airport::typeToString(Airport::Type::MEDIUM_AIRPORT) << "Kitchen Creek Helibase Heliport" << "32000ft"
         << "NA" << "US" << "US-PA-U" << "Altamonte Springs" << "AAAA" << "AAA" << airports.front()->getLatitude()
         << airports.front()->getLongitude() << endl;
    
    /*
    for(Airport* a: airports){
        cout << Airport::typeToString(a->getType()) << " | " << a->getName() << " | " << a->getElevation()
            << "ft | " << a->getContinent() << " | " << a->getRegion() << " | " << a->getMunicipality()
            << " | " << a->getICAOCode() << " | " << a->getIATACode() << " | " << a->getGPSCode()
            << " | " << a->getLocalCode() << " | " << a->getLatitude() << " | " << a->getLongitude() << endl;
    }
    */
}