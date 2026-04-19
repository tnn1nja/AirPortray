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
    cout << left << fixed
         << setw(15) << "Type" << "| "
         << setw(32) << "Name" << "| "
         << "Elevation (ft) | "
         << "Continent | "
         << "Country | " 
         << "Region | " 
         << setw(20) << "Municipality" << "| "
         << "ICAO Code | "
         << "IATA Code | " 
         << "GPS Code | " 
         << "Local Code | " 
         << "Coordinates"
         << endl;

    cout << setw(15) << Airport::typeToString(Airport::Type::MEDIUM_AIRPORT) << "| "
         << setw(32) << "Kitchen Creek Helibase Heliport" << "| "
         << setw(15) << "32000" << "| "
         << setw(10) << "NA" << "| "
         << setw(8) << "US" << "| "
         << setw(7) << "US-PAU" << "| "
         << setw(20) << "Altamonte Springs" << "| "
         << setw(10) << "AAAA" << "| "
         << setw(10) << "BBB" << "| "
         << setw(9) << "CCCC" << "| "
         << setw(11) << "DDDD" << "| "
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