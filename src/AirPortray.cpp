#include "include/AirPortray.h"
#include <iostream>

AirPortray::AirPortray(std::string dataFilePath){
    airportRepository = new AirportRepository(dataFilePath);
}
void AirPortray::run(){
    std::cout << "AirPortray running!\n";
}