#include "include/AirportDataFile.h"
#include <iostream>
#include <fstream>

using namespace std;

AirportDataFile::AirportDataFile(string filePath) : filePath(filePath) {}

void AirportDataFile::load(list<Airport>& airports){
    ifstream file(filePath);
    if (!file.is_open()){
        cout <<
    }
}