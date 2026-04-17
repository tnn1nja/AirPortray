#ifndef AIRPORTREPOSITORY_H
#define AIRPORTREPOSITORY_H

#include <list>
#include "Airport.h"
#include "AirportDataFile.h"

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile *dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository();
        void saveIfDirty();
};

#endif