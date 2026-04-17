#include "include/AirportDataFile.h"
#include <iostream>

AirportDataFile::AirportDataFile(std::string filePath){
    this->filePath = filePath;
}

void AirportDataFile::load(std::list<Airport>& airports){
    std::cout << "Data file loaded\n";
}