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
    for(Airport* a: airports){
        cout << Airport::typeToString(a->getType()) << " " << a->getName() << " " << a->getElevation()
            << " " << a->getContinent() << " " << a->getRegion() << " " << a->getMunicipality()
            << " " << a->getICAOCode() << " " << a->getIATACode() << " " << a->getGPSCode()
            << " " << a->getLocalCode() << " " << a->getLatitude() << " " << a->getLongitude() << endl;
    };
}