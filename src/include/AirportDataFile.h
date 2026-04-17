#pragma once

#include <list>
#include <string>
#include "include/Airport.h"

class AirportDataFile{
    private:
        std::string filePath;

    public:
        AirportDataFile(std::string filePath);
        void load(std::list<Airport>&);
        void save(std::list<Airport>&);
};