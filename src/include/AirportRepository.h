#pragma once

#include "Airport.h"
#include "AirportDataFile.h"
#include <vector>
#include <functional>
#include <algorithm>

#define DEG_TO_RAD_CONST 3.14159/180
#define EARTH_RADIUS 6371000

class AirportRepository{
    private:
        std::list<Airport> airports;
        AirportDataFile* dataFile;
        bool dirty;

    public:
        AirportRepository(std::string);
        ~AirportRepository() {};

        void save();
        std::vector<Airport*> getAirports();
        void filterByField(std::vector<Airport*>&, std::function<bool(Airport*)>);
        unsigned int calculateDistanceBetweenAirports(Airport* a1, Airport* a2);

        //Template methods (must be implemented in header)
        template <typename FieldType>
        void sortByField(std::vector<Airport*>& airports, std::function<FieldType(Airport*)> getField){
            auto comparator = [getField](Airport* a1, Airport* a2){return getField(a1) < getField(a2);};
            sort(airports.begin(), airports.end(), comparator);
        }
};