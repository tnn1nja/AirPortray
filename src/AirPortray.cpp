#include "include/AirPortray.h"

AirPortray::AirPortray(std::string dataFilePath){
    airportRepository = AirportRepository(dataFilePath);
}