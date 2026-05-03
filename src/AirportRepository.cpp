#include "include/AirportRepository.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cmath>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    if (!dataFile->load(airports)){
        throw runtime_error("cannot open data file at: " + dataFilePath + "!");
    }
    dirty = false;
}

AirportRepository::~AirportRepository(){
    delete(dataFile);
}

void AirportRepository::save(){
    if(dirty){
        if (!dataFile->save(airports)){
             throw runtime_error("cannot open data file, maybe you already have it open?");
        }
    }
    dirty = false;
}

void AirportRepository::addAirport(Airport a){
    airports.push_back(a);
    dirty = true;
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

unsigned int AirportRepository::calculateDistanceFromCoordinates(Airport* a, double latitude, double longitude){
    double phi1 = a->getLatitude()*PI/180;
    double lambda1 = a->getLongitude()*PI/180;
    double phi2 = latitude*PI/180;
    double lambda2 = longitude*PI/180;

    double deltaPhi = phi2 - phi1;
    double deltaLambda = lambda2 - lambda1;
    double haversineTheta = (1-cos(deltaPhi)+cos(phi1)*cos(phi2)*(1-cos(deltaLambda)))/2;
    double theta = 2*asin(sqrt(haversineTheta));

    return theta*EARTH_RADIUS;
}

unsigned int AirportRepository::calculateDistanceBetweenAirports(Airport* a1, Airport* a2){
    return calculateDistanceFromCoordinates(a1, a2->getLatitude(), a2->getLongitude());
}