#pragma once

#include "Airport.h"
#include "AirportDataFile.h"
#include <vector>
#include <functional>

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile* dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository();

        void save();
        std::vector<Airport*> sortByField(vector<Airport*>, function<string> getField);

        std::vector<Airport*> getSomeAirports();
};