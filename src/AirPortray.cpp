#include "include/AirPortray.h"
#include <iostream>

using namespace std;

AirPortray::AirPortray(string dataFilePath){
    airportRepository = new AirportRepository(dataFilePath);
}

void AirPortray::run(){
    cout << "AirPortray running!\n";
    airportRepository->test();
}