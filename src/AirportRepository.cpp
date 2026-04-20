#include "include/AirportRepository.h"
#include <iostream>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    dataFile->load(airports);
    dirty = false;
}

bool AirportRepository::saveIfDirty(){
    if(dirty){
        dataFile->save(airports);
        cout << "AirportData altered, saving...\n";
    }
    return dirty;
}