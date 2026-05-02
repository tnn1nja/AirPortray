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
        ~AirportRepository() {};

        void save();
        //template <typename T>
        void sortByField(std::vector<Airport*>&, std::function<std::string(Airport*)> getField);

        std::vector<Airport*> getSomeAirports();
};