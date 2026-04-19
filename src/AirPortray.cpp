#include "include/AirPortray.h"
#include <iostream>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    repository = new AirportRepository(dataFilePath);
}

void AirPortray::run(){
    cout << "AirPortray running!\n";
    displayAirports();
    repository->saveIfDirty();
}

void AirPortray::displayAirports(list<Airport&> airports){

}