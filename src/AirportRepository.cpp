#include "include/AirportRepository.h"

AirportRepository::AirportRepository(std::string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
}