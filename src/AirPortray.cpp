#include "include/AirPortray.h"

AirPortray::AirPortray(std::string dataFilePath){
    airportRepository = new AirportRepository(dataFilePath);
}