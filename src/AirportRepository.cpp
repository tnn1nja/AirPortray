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

void AirportRepository::filterByField(vector<Airport*>& airports, std::function<bool(Airport*)> isValid){
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

void AirportRepository::filterByDistanceFromCoordinates(vector<Airport*>& airports, double latitude, double longitiude, unsigned int radius){
    auto i = airports.begin();
    while(i != airports.end()){
        if (calculateDistanceFromCoordinates((*i), latitude, longitiude) <= radius){
            i++;
        }else{
            airports.erase(i);
        }
    }
}

void AirportRepository::sortByDistanceFromCoordinates(std::vector<Airport*>& airports, double latitude, double longitude){
    auto comparator = [this, latitude, longitude](Airport* a1, Airport* a2){
        return calculateDistanceFromCoordinates(a1, latitude, longitude) <
            calculateDistanceFromCoordinates(a2, latitude, longitude);
    };
    sort(airports.begin(), airports.end(), comparator);
}

map<Airport::Type, unsigned int> AirportRepository::calculateAirportCountByType(){
    int counts[NUM_AP_TYPES];
    for(int i=0; i<NUM_AP_TYPES; i++){
        counts[i] = 0;
    }

    auto a = airports.begin();
    while(a != airports.end()){
        counts[static_cast<int>((*a).getType())]++;
        a++;
    }

    map<Airport::Type, unsigned int> output;
    for(int i=0; i<NUM_AP_TYPES; i++){
        output[static_cast<Airport::Type>(i)] = counts[i];
    }
    return output;
}

Airport* AirportRepository::getAirportByIATA(string IATA){
    auto a = airports.begin();
    while(a != airports.end()){
        if((*a).getIATACode() == IATA){
            return &(*a);
        }
        a++;
    }
    return nullptr;
}