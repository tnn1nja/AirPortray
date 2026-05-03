#include "include/AirportRepository.h"
#include <algorithm>
#include <stdexcept>
#include <cmath>

using namespace std;

//Constructor and destructor
AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    if (!dataFile->load(airports)){ //load automatically on init
        throw runtime_error("cannot open data file at: " + dataFilePath + "!");
    }
    dirty = false;
}

AirportRepository::~AirportRepository(){
    delete(dataFile); //created with new so lasts out of scope
}

//Public methods
void AirportRepository::save(){
    if(dirty){
        if (!dataFile->save(airports)){
             throw runtime_error("cannot open data file, maybe you already have it open?");
        }
    }
    dirty = false;
}

void AirportRepository::addAirport(Airport a){
    airports.push_back(a); //validation done in setters
    dirty = true; //needs saving
}

vector<Airport*> AirportRepository::getAirports(){
    //Convert to vector of pointers
    vector<Airport*> output;
    for(auto i = airports.begin(); i != airports.end(); i++){
        output.push_back(&*i);
    }
    return output;
}

void AirportRepository::filterByField(vector<Airport*>& airports, std::function<bool(Airport*)> isValid){
    auto i = airports.begin();
    while(i != airports.end()){
        if (isValid(*i)){ //filter by result of lambda for modularity
            i++; //skip
        }else{
            airports.erase(i); //don't increment to account for erasure
        }
    }
}

unsigned int AirportRepository::calculateDistanceFromCoordinates(Airport* a, double latitude, double longitude){
    //Convert to radians
    double phi1 = a->getLatitude()*PI/180;
    double lambda1 = a->getLongitude()*PI/180;
    double phi2 = latitude*PI/180;
    double lambda2 = longitude*PI/180;

    //Find deltas
    double deltaPhi = phi2 - phi1;
    double deltaLambda = lambda2 - lambda1;

    //Find angle change
    double haversineTheta = (1-cos(deltaPhi)+cos(phi1)*cos(phi2)*(1-cos(deltaLambda)))/2;
    double theta = 2*asin(sqrt(haversineTheta));

    //Convert to distance
    return theta*EARTH_RADIUS;
}

unsigned int AirportRepository::calculateDistanceBetweenAirports(Airport* a1, Airport* a2){
    return calculateDistanceFromCoordinates(a1, a2->getLatitude(), a2->getLongitude());
}

void AirportRepository::filterByDistanceFromCoordinates(vector<Airport*>& airports, double latitude, double longitiude, unsigned int radius){
    auto i = airports.begin();
    while(i != airports.end()){
        if (calculateDistanceFromCoordinates((*i), latitude, longitiude) <= radius){
            i++; //skip
        }else{
            airports.erase(i); //don't increment to account for erasure
        }
    }
}

void AirportRepository::sortByDistanceFromCoordinates(std::vector<Airport*>& airports, double latitude, double longitude){
    auto comparator = [this, latitude, longitude](Airport* a1, Airport* a2){
        return calculateDistanceFromCoordinates(a1, latitude, longitude) <
            calculateDistanceFromCoordinates(a2, latitude, longitude); //ascending
    };
    sort(airports.begin(), airports.end(), comparator);
}

map<Airport::Type, unsigned int> AirportRepository::calculateAirportCountByType(){
    //Initialise empty array
    int counts[NUM_AP_TYPES];
    for(int i=0; i<NUM_AP_TYPES; i++){
        counts[i] = 0;
    }

    //Cast type to int to count
    for(auto a = airports.begin(); a != airports.end(); a++){
        counts[static_cast<int>((*a).getType())]++;
    }

    //Convert to map for return
    map<Airport::Type, unsigned int> output;
    for(int i=0; i<NUM_AP_TYPES; i++){
        output[static_cast<Airport::Type>(i)] = counts[i];
    }
    return output;
}

Airport* AirportRepository::getAirportByIATA(string IATA){
    for(auto i = airports.begin(); i != airports.end(); i++){
        if((*i).getIATACode() == IATA){
            return &(*i); //early return
        }
    }
    return nullptr; //not found
}