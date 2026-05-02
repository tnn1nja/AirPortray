#include "include/AirportRepository.h"
#include <iostream>
#include <algorithm>
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
vector<Airport*> AirportRepository::getAirports(){
    vector<Airport*> output;
    auto a = airports.begin();
    while(a != airports.end()){
        output.push_back(&*a);
        a++;
    }
    return output;
}