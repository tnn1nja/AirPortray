#pragma once

#include <list>
#include <include/Airport.h>
#include <include/AirportDataFile.h>

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository();
        void saveIfDirty();
};