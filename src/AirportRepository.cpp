#include "include/AirportRepository.h"
#include <iostream>

using namespace std;

AirportRepository::AirportRepository(string dataFilePath){
    dataFile = new AirportDataFile(dataFilePath);
    dataFile->load(airports);
}

void AirportRepository::test(){
    cout << airports.front().getName() << endl;
}