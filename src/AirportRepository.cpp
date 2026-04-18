#include "include/AirportRepository.h"
#include <iostream>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    dataFile->load(airports);
}

void AirportRepository::test(){
    list<Airport>::iterator a = airports.begin();
    for(int i=0; i<24445; i++){
        a++;
    }

    cout << static_cast<int>(a->getType()) << " " << a->getName() << " " << a->getElevation()
         << " " << a->getContinent() << " " << a->getRegion() << " " << a->getMunicipality()
         << " " << a->getICAOCode() << " " << a->getIATACode() << " " << a->getGPSCode()
         << " " << a->getLocalCode() << " " << a->getLatitude() << " " << a->getLongitude() << endl;
}