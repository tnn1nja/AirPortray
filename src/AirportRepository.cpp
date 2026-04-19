#include "include/AirportRepository.h"
#include <iostream>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    dataFile->load(airports);
    dirty = true;//false;
}

bool AirportRepository::saveIfDirty(){
    if(!dirty){
        dataFile->save(airports);
    }
    return !dirty;
}