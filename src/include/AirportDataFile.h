#pragma once

#include <list>
#include <string>
#include "include/Airport.h"

class AirportDataFile{
    private:
        std::string filePath;

    public:
        void load(std::list<Airport>&);
        void save(std::list<Airport>&);
};