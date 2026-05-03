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

vector<Airport*> AirportRepository::getAirports(){
    vector<Airport*> output;
    auto i = airports.begin();
    while(i != airports.end()){
        output.push_back(&*i);
        i++;
    }
    return output;
}

void AirportRepository::filterByField(std::vector<Airport*>& airports, std::function<bool(Airport*)> isValid){
    auto i = airports.begin();
    while(i != airports.end()){
        if (isValid(*i)){
            i++;
        }else{
            airports.erase(i);
        }
    }
}

unsigned int AirportRepository::calculateDistanceBetweenAirports(Airport* a1, Airport* a2){
}