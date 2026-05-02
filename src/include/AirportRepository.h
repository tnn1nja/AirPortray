#pragma once

#include "Airport.h"
#include "AirportDataFile.h"
#include <vector>

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile* dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository();

        void save();
};