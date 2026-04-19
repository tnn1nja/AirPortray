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

//TEMPORARY
std::list<Airport*> AirportRepository::getSomeAirports(){
    list<Airport*> output;
    list<Airport>::iterator a = airports.begin();
    for(int i=0;i<10;i++){
        output.push_back(&(*a));
        a++;
    }
    return output;
}