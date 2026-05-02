#include "include/AirportRepository.h"
#include <iostream>
#include <stdexcept>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    if (!dataFile->load(airports)){
        throw runtime_error("Data file cannot be opened");
    }
    dirty = false;
}

void AirportRepository::save(){
    if(dirty){
        if (!dataFile->save(airports)){
            throw runtime_error("Data file cannot be opened");
        }
    }
    dirty = false;
}

//TEMPORARY
vector<Airport*> AirportRepository::getSomeAirports(){
    vector<Airport*> output;
    list<Airport>::iterator a = airports.begin();
    for(int i=0;i<100;i++){
        output.push_back(&(*a));
        a++;
    }
    return output;
}